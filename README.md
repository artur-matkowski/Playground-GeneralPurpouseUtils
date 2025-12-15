# BitForge Utils (Playground-GeneralPurpouseUtils)

A comprehensive C++ utility library providing general-purpose components for embedded systems and high-performance applications. This library is particularly optimized for ARM architectures (armhf) and x86-64 (amd64) platforms.

## Features

### Core Components

- **Custom Memory Allocators**: Pre-allocated, standard, and forward memory allocation strategies
  - `PreAllocatedMemBlock`: Fixed-size memory pool allocation
  - `StdAllocatorMemBlock`: Standard allocator wrapper
  - `ForwardAllocatorMemBlock`: Sequential memory allocation
  - `MemBlockBase`: Base class for custom memory management

- **Advanced Logging System**: Flexible logging with multiple severity levels
  - File and console logging support
  - Debug levels: ALL, INFO, WARNING, ERROR
  - Timestamp and location tracking
  - Convenient macros: `error`, `warning`, `info`, `debug`

- **Stream Utilities**: Custom stream implementation with memory management
  - Type-safe output operations
  - Integration with custom allocators
  - Buffer management

- **UDP Networking**: UDP socket communication utilities
  - Network event handling
  - Integration with event system

- **Event System**: Publish-subscribe event handling
  - Type-safe event dispatching
  - Extensible event architecture

- **Object Serialization**: Multiple serialization formats
  - **JSON Serialization**: Human-readable object serialization
  - **Binary Serialization**: Efficient binary format for fast I/O
  - Macro-based serialization definitions
  - Automatic serialization/deserialization

## Requirements

### Build Dependencies

- **Compiler**: g++ with C++14 support (gcc 8.3+ recommended)
- **Build Tools**: 
  - GNU Make
  - bash
  - dpkg (for packaging)
  - lsb-release (for distribution detection)

### Supported Platforms

- **Architectures**: 
  - armhf (ARM hard-float)
  - amd64 (x86-64)
- **Operating Systems**: Linux (Debian-based distributions)

## Building the Project

### Prerequisites

```bash
# Ensure you have the required tools
sudo apt-get install build-essential g++ make dpkg-dev
```

### Build Commands

The project uses a Makefile with multiple build targets:

```bash
# Build both debug and release versions
make all

# Build debug version only (with full debug symbols and logging)
make debug

# Build release version only (optimized, minimal logging)
make release

# Clean build artifacts
make clean
```

### Build Outputs

Build artifacts are organized by architecture and build type:
```
build/
├── amd64/
│   ├── dbg/          # Debug build
│   └── rel/          # Release build
└── armhf/
    ├── dbg/          # Debug build
    └── rel/          # Release build
```

Each build directory contains:
- `bitforgeutils_tests`: Test executable
- Object files (*.o)

## Testing

The project includes comprehensive test suites for all major components.

### Running Tests

```bash
# Build and run specific test suites
./build/<architecture>/rel/bitforgeutils_tests <test-suite>
```

### Available Test Suites

| Test Suite | Command | Description |
|------------|---------|-------------|
| Stream Tests | `stream` | Tests stream utilities and output formatting |
| Logging Tests | `logging` | Tests logging system with various levels |
| UDP Tests | `udp` | Tests UDP networking functionality |
| Event Tests | `event` | Tests event system and dispatching |
| JSON Serialization | `serialj` | Tests JSON object serialization |
| Binary Serialization | `serialb` | Tests binary object serialization |

### Example

```bash
# Run stream tests on amd64 release build
./build/amd64/rel/bitforgeutils_tests stream

# Run all tests (for ARM hard-float debug build)
./build/armhf/dbg/bitforgeutils_tests logging
./build/armhf/dbg/bitforgeutils_tests udp
./build/armhf/dbg/bitforgeutils_tests event
./build/armhf/dbg/bitforgeutils_tests serialj
./build/armhf/dbg/bitforgeutils_tests serialb
```

## Usage Example

### Basic Memory Allocation

```cpp
#include <bfu.hpp>

// Create a pre-allocated memory block
char* buffer = new char[1024*1024];
PreAllocatedMemBlock memblock(buffer, 1024*1024, "my memory block");

// Allocate from the block
float* data = (float*)memblock.allocate(1, sizeof(float), alignof(float));
*data = 3.14f;

// Deallocate
MemBlockBase::DeallocateUnknown(data);
delete[] buffer;
```

### Logging

```cpp
#include <bfu.hpp>

// Use logging macros
debug << "Debug information" << std::endl;
info << "Information message" << std::endl;
warning << "Warning message" << std::endl;
error << "Error occurred!" << std::endl;
```

### Object Serialization

```cpp
#include <bfu.hpp>

// Define a serializable class
class MyClass : public bfu::SerializableClassBase<MyClass> {
public:
    SERIALIZABLE_VAR(MyClass, int, myInt);
    SERIALIZABLE_VAR(MyClass, float, myFloat);
    
    MyClass() {}
    ~MyClass() {}
};

// Serialize to JSON
bfu::JSONSerializer jsonSerializer;
MyClass obj;
obj.myInt = 42;
obj.myFloat = 3.14f;
std::string json = obj.serialize(jsonSerializer);

// Serialize to binary
bfu::BinarySerializer binSerializer;
std::vector<uint8_t> binary = obj.serialize(binSerializer);
```

## Continuous Integration

The project uses GitLab CI for automated building and testing across multiple architectures.

### CI Pipeline Stages

1. **Build**: Compiles debug and release versions for both armhf and amd64
2. **Tests**: Runs all test suites automatically
3. **Deploy**: Creates Debian packages for stable and test branches
4. **UpdateRepo**: Updates the package repository

### Artifacts

Each CI run produces:
- Build logs in `Logs/` directory
- Compiled binaries in `build/` directory
- Debian packages (`.deb` files) for deployment

## Packaging

The project can be packaged into Debian packages for easy distribution and installation.

### Creating Packages

```bash
# Create packages for a specific branch
./package.sh <branch-name>
```

This creates three packages:
- **bitforgeutils**: Runtime library package
- **bitforgeutils-dev**: Development headers package
- **bitforgeutils-dev-dbg**: Debug symbols package

### Package Installation

```bash
# Install the runtime library
sudo dpkg -i Playground-GeneralPurpouseUtils-<version>_<arch>.deb

# Install development package
sudo dpkg -i Playground-GeneralPurpouseUtils-<version>_<arch>-dev.deb

# Install debug symbols (optional)
sudo dpkg -i Playground-GeneralPurpouseUtils-<version>_<arch>-dev-dbg.deb
```

## Project Structure

```
.
├── inc/                          # Header files
│   ├── Allocators/              # Memory allocator headers
│   ├── ObjectSerialization/     # Serialization headers
│   ├── bfu.hpp                  # Main include file
│   ├── log.hpp                  # Logging system
│   ├── stream.hpp               # Stream utilities
│   ├── udp.hpp                  # UDP networking
│   └── EventSystem.hpp          # Event system
├── src/                         # Source implementation files
│   ├── Allocators/              # Memory allocator implementations
│   └── ObjectSerialization/     # Serialization implementations
├── tests/                       # Test suites
├── main.cpp                     # Test runner application
├── makefile                     # Build configuration
├── .gitlab-ci.yml               # CI/CD configuration
└── README.md                    # This file
```

## Contributing

This is a playground/experimental repository for general-purpose utilities. Contributions and improvements are welcome.

## License

Please check with the repository maintainer for licensing information.

## Additional Notes

- The library is designed with embedded systems in mind, supporting custom memory management
- All tests must pass on both armhf and amd64 architectures before deployment
- Debug builds include comprehensive logging; release builds are optimized for performance
- The serialization system supports both human-readable (JSON) and efficient binary formats
