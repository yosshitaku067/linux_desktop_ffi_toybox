extern crate libc;

#[link(name = "mylibrary")]
extern "C" {
    fn add(num1: i32, num2: i32) -> i32;
}

#[no_mangle]
pub extern "C" fn increment(num: i32) -> i32 {
    let mut x = 0;
    unsafe {
        x = add(num, 1);
    };
    println!("called increment bridge");
    return x;
}


#[cfg(test)]
mod tests {
    use crate::api::increment;

    #[test]
    fn it_works() {

        increment(1);

        assert_eq!(2 + 2, 4);
    }
}