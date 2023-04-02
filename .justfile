set shell := ["/bin/bash", "-c"]

# Rustのビルド
build-debug-rust:
    cd rust && cargo build

build-release-rust:
    cd rust && cargo build --release

# flutter_rust_bridge_codegen の実行
codegen:
    flutter_rust_bridge_codegen --rust-input rust/src/api.rs --dart-output lib/generated/brige_generated.dart 

# asn1c setup
asn-setup:
    cd c && bash ./setup.sh

# asn1c clean
asn-clean:
    cd c && bash ./clean.sh

# flutter run
run:
    flutter run