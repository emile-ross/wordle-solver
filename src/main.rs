use std::ffi::{CStr, c_char};

fn main()
{
    let arguments: Vec<String> = std::env::args().collect();
    let argc: i32 = std::env::args().count().try_into().unwrap();
    unsafe {
        c_main(argc, arguments);
    }
    println!("Hi");
}

unsafe extern "C" {
    fn c_main(argc: i32, argv: Vec<String>) -> i32;
}
