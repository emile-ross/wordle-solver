use std::ffi::CString;
use std::os::raw::{c_char, c_int};

fn main()
{
    let arguments: Vec<CString> = std::env::args()
        .map(|arg| CString::new(arg).unwrap())
        .collect();

    let mut argv: Vec<*const c_char> = arguments
        .iter()
        .map(|arg| arg.as_ptr())
        .collect();

    argv.push(std::ptr::null());

    let argc = (arguments.len()) as c_int;

    unsafe {
        c_main(argc, argv.as_ptr());
    }
}

unsafe extern "C" {
    fn c_main(argc: c_int, argv: *const *const c_char) -> c_int;
}
