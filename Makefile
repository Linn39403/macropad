SHELL := /bin/bash
.ONESHELL:

REPO_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
QMK_DIR ?= $(REPO_ROOT)/vendor/qmk_firmware
QMK_REF ?= 0.32.13
KEYBOARD ?= linn/macropad
KEYMAP ?= default
JOBS ?= $(shell nproc 2>/dev/null || echo 1)
PYTHON ?= python3

KEYBOARD_SOURCE := $(REPO_ROOT)/firmware/macropad_4x5_rot_3
KEYBOARD_DIR := $(QMK_DIR)/keyboards/$(KEYBOARD)
BUILD_DIR := $(REPO_ROOT)/build
ARTIFACT_NAME := $(subst /,_,$(KEYBOARD))_$(KEYMAP).uf2
QMK_ARTIFACT := $(QMK_DIR)/.build/$(ARTIFACT_NAME)
ARTIFACT := $(BUILD_DIR)/$(ARTIFACT_NAME)
UPLOADER := $(REPO_ROOT)/firmware/host_side/upload_firmware.py
QMK_SUBMODULES := lib/chibios lib/chibios-contrib lib/pico-sdk lib/lvgl lib/lufa lib/printf

.DEFAULT_GOAL := firmware
.PHONY: all firmware upload test-host setup sync doctor clean help

all: firmware

firmware: sync
	@set -euo pipefail
	if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
		printf '%s\n' 'ARM GCC is missing. Run make setup first.' >&2
		exit 1
	fi
	SKIP_GIT=yes QMK_HOME="$(QMK_DIR)" $(MAKE) -C "$(QMK_DIR)" "$(KEYBOARD):$(KEYMAP)" -j"$(JOBS)"
	if [[ ! -f "$(QMK_ARTIFACT)" ]]; then
		printf 'Expected QMK artifact was not produced: %s\n' "$(QMK_ARTIFACT)" >&2
		exit 1
	fi
	mkdir -p "$(BUILD_DIR)"
	cp "$(QMK_ARTIFACT)" "$(ARTIFACT)"
	printf 'Firmware written to %s\n' "$(ARTIFACT)"

upload: firmware
	@set -euo pipefail
	"$(PYTHON)" "$(UPLOADER)" --firmware "$(ARTIFACT)"

test-host:
	@set -euo pipefail
	"$(PYTHON)" -m unittest discover -s "$(REPO_ROOT)/firmware/host_side/tests" -p 'test_*.py'

setup:
	@set -euo pipefail
	if ! command -v qmk >/dev/null 2>&1; then
		printf '%s\n' 'The QMK CLI is required. Install it with: python3 -m pip install --user qmk' >&2
		exit 1
	fi
	if [[ -d "$(QMK_DIR)/.git" ]]; then
		if [[ -n "$$(git -C "$(QMK_DIR)" status --porcelain)" ]]; then
			printf 'Refusing to modify dirty QMK checkout: %s\n' "$(QMK_DIR)" >&2
			exit 1
		fi
		git -C "$(QMK_DIR)" fetch --depth 1 origin "refs/tags/$(QMK_REF):refs/tags/$(QMK_REF)"
		git -C "$(QMK_DIR)" checkout --detach "$(QMK_REF)"
	else
		mkdir -p "$$(dirname "$(QMK_DIR)")"
		git clone --depth 1 --branch "$(QMK_REF)" https://github.com/qmk/qmk_firmware.git "$(QMK_DIR)"
	fi
	git -C "$(QMK_DIR)" submodule update --init $(QMK_SUBMODULES)
	if ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
		if grep -Eq '^(ID|ID_LIKE)=.*(debian|ubuntu)' /etc/os-release; then
			(
				cd "$(QMK_DIR)"
				QMK_FIRMWARE_DIR="$(QMK_DIR)" SKIP_PROMPT=-y bash -c '. util/install/debian.sh; _qmk_install_prepare; _qmk_install'
			)
		else
			"$(QMK_DIR)/util/qmk_install.sh" -y
		fi
	fi
	for submodule in $(QMK_SUBMODULES); do
		status="$$(git -C "$(QMK_DIR)" submodule status "$$submodule")"
		if [[ "$$status" == -* ]]; then
			printf 'Required QMK submodule is unavailable: %s\n' "$$submodule" >&2
			exit 1
		fi
	done

sync:
	@set -euo pipefail
	if [[ ! -d "$(QMK_DIR)/.git" ]]; then
		printf '%s\n' 'QMK framework is missing. Run make setup first.' >&2
		exit 1
	fi
	mkdir -p "$(KEYBOARD_DIR)"
	rsync -a --delete --exclude='.git' "$(KEYBOARD_SOURCE)/" "$(KEYBOARD_DIR)/"

doctor:
	@set -euo pipefail
	if [[ ! -d "$(QMK_DIR)/.git" ]]; then
		printf '%s\n' 'QMK framework is missing. Run make setup first.' >&2
		exit 1
	fi
	if ! command -v qmk >/dev/null 2>&1 || ! command -v arm-none-eabi-gcc >/dev/null 2>&1; then
		printf '%s\n' 'QMK CLI or ARM GCC is missing. Run make setup first.' >&2
		exit 1
	fi
	for submodule in $(QMK_SUBMODULES); do
		status="$$(git -C "$(QMK_DIR)" submodule status "$$submodule")"
		if [[ "$$status" == -* ]]; then
			printf 'Required QMK submodule is unavailable: %s\n' "$$submodule" >&2
			exit 1
		fi
	done
	printf '%s\n' 'QMK build prerequisites are available.'

clean:
	rm -rf "$(BUILD_DIR)"

help:
	@printf '%s\n' \
		'Commands:' \
		'  make setup    Clone pinned QMK and install build dependencies.' \
		'  make          Synchronize and compile the default firmware.' \
		'  make upload   Build firmware, enter the RP2040 bootloader, and copy the UF2.' \
		'  make test-host Run uploader unit tests.' \
		'  make doctor   Check required QMK build prerequisites.' \
		'  make clean    Remove copied firmware artifacts.' \
		'' \
		'Overrides: KEYMAP=<name> JOBS=<count> QMK_DIR=<path> QMK_REF=<ref>'
