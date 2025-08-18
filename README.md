[![Build Status](https://github.com/danilrudin/XOR-FileEncryptor/workflows/Build/badge.svg)](https://github.com/danilrudin/XOR-FileEncryptor/actions/workflows/build.yml) [![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=danilrudin_XOR-FileEncryptor&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=danilrudin_XOR-FileEncryptor) [![GitHub license](https://badgen.net/github/license/danilrudin/XOR-FileEncryptor)](https://github.com/danilrudin/XOR-FileEncryptor/blob/master/LICENSE)

# XOR-FileEncryptor

A simple file encryption utility based on the XOR algorithm.

**⚠️ Note:** XOR is not cryptographically secure and should be used only for educational or simple utility purposes.

---

## 🔧 Usage

The program is run from the CLI.

```bash
FileEncryptor.exe [-e | -d] [-k <key> | -g] -i <input_file> -o <output_file>
```

### Options

- `-e` — encrypt the input file
- `-d` — decrypt the input file
- `-k <key>` — specify encryption key (string)
- `-g` — generate a random key
- `-i <input_file>` — input file path
- `-o <output_file>` — output file path

Examples:

```bash
# Encrypt file.txt to file.enc with key "secret"
FileEncryptor.exe -e -k secret -i file.txt -o file.enc

# Decrypt file.enc back to file.txt with key "secret"
FileEncryptor.exe -d -k secret -i file.enc -o file.txt
```

---

## 📦 Build

### Linux / macOS

```bash
cmake -B build -S .
cmake --build build --config Release
```

### Windows (MinGW)

```bash
cmake -B build -S . -G "MinGW Makefiles"
cmake --build build --config Release
```
