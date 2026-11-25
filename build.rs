fn main()
{
    let file_paths = vec![
        "src/main.c",
        "src/match_store.c",
        "src/validate.c",
        "src/memory/buffers.c",
        "src/memory/checks.c",
        "src/errors.c",
        "src/config.c",
        "src/command_parsing.c",
        "src/file_reading.c",
        "src/globals.c"];

    cc::Build::new().files(file_paths)
        .compile("c_unsafe_functions");
}
