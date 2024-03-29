.POSIX:
.PHONY: clean
.ONESHELL:
.NOTPARALLEL:

CUR_DIR := $(shell basename $(CURDIR))
CC := gcc
CFLAGS := -W -Wall -Wno-unused-parameter -Wno-unused-variable -Werror -std=c11 -pedantic -lc -D_POSIX_C_SOURCE=200809L
EXFILE := main
SSH_SERVER := undertaken@172.20.10.2
SERVER_PATH := ~/$(CUR_DIR)

all: remote_build

remote_build:
	rsync --delete -r $(CURDIR)/ "$(SSH_SERVER):$(SERVER_PATH)"
	ssh $(SSH_SERVER) "cd $(SERVER_PATH) && $(CC) $(CFLAGS) $(EXFILE).c -o $(EXFILE)"

build:
	$(CC) $(CFLAGS) $(EXFILE).c -o $(EXFILE)

clean:
	rm $(EXFILE)

