CC ?= cc
CFLAGS ?=
LDLIBS ?= -lmysqlclient -lsqlite3 -lcurl -lssl -lcrypto -lpthread -lm

SRC := $(sort $(wildcard src/*.c))
BIN := $(patsubst src/%.c,bin/%,$(SRC))

.PHONY: all check clean
all: $(BIN)

bin/%: src/%.c | bin
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

bin:
	mkdir -p bin

check:
	@for f in $(SRC); do $(CC) $(CFLAGS) -fsyntax-only $$f || echo "failed: $$f"; done

clean:
	rm -rf bin
