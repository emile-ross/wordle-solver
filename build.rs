fn main()
{
    /* TODO dynamically write the file paths using the directories instead
     * of this hard coded strings approach */

    let file_paths = vec![
        "src/command_parsing.c",
        "src/config.c",
        "src/errors.c",
        "src/file_reading.c",
        "src/globals.c",
        "src/main.c",
        "src/match_store.c",
        "src/parsing.c",
        "src/validate.c",
        "src/libs/compare.c",
        "src/libs/ctype.c",
        "src/lists/list_matching.c",
        "src/lists/name.c",
        "src/memory/buffers.c",
        "src/memory/checks.c",
        "src/printing/table.c",
        "src/printing/texts.c",
        "src/printing/verbose.c"
    ];

    cc::Build::new().files(file_paths)
        .debug(true)
        .warnings(true)
        .compile("c_unsafe_functions");
}
