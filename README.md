# C programs

A collection of small, self-contained C programs. Each file in `src/` is a
complete program with its own `main`.

## Building

    make -k

builds every program into `bin/`. The programs use the C standard library,
POSIX, and in some cases the MySQL client, SQLite3, libcurl and OpenSSL
libraries; install their development headers first (on Debian/Ubuntu:
`libmysqlclient-dev libsqlite3-dev libcurl4-openssl-dev libssl-dev`).
`make check` runs a syntax-only pass over every file. `-k` keeps the build
going if an individual program fails to build.

## License

MIT. See `LICENSE` and `NOTICE`.
