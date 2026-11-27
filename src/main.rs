use std::ffi::CString;
use std::os::raw::{c_char, c_int};

fn main()
{
    // arguments_parsing(std::env::args().collect());

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

fn _arguments_parsing(argv: Vec<String>)
{
    /* iterates over the argument array with the i iterator */
    for (i, arg) in argv.iter().enumerate()
    {
        if arg == "-w" || arg == "--word-list"
        {
            println!("Argument is -w at pos {}", i);
        }
    }
}

unsafe extern "C" {
    fn c_main(argc: c_int, argv: *const *const c_char) -> c_int;
}
