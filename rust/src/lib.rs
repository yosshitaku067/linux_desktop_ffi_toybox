// no_mangleについて
// https://tomoyuki-nakabayashi.github.io/book/interoperability/rust-with-c.html#no_mangle
#[no_mangle]
pub extern fn increment(num: i32) -> i32 {
    let x: i32 = num + 1;
    println!("called increment");
    return x;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_increment() {
        assert_eq!(6, increment(1));
    }
}
