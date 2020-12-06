// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "rdump",
    products: [
      .library(name: "MachO", targets: ["MachO"]),
      .executable(name: "rdump", targets: ["rdump"]),
    ],
    dependencies: [
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(
            name: "rdump",
            dependencies: ["LLVMSupport"]),
        .target(
          name: "MachO",
          dependencies: ["LLVMSupport"]),
        // Copy of a subset of llvm's ADT and Support libraries.
        .target(
          name: "LLVMSupport",
          dependencies: [],
          path: "lib/LLVMSupport"),
        .testTarget(
            name: "rdumpTests",
            dependencies: ["rdump"]),
    ],
  
    cxxLanguageStandard: .cxx14
)
