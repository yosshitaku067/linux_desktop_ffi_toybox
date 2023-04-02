fn main() {
    println!("cargo:rustc-link-search=native=../c/out");
    println!("cargo:rustc-link-lib=static=mylibrary");
}
