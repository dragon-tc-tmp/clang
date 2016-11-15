// REQUIRES: system-darwin

// Check that ld gets "-lto_library" and warnings about libLTO.dylib path.

// RUN: mkdir -p %T/bin
// RUN: mkdir -p %T/lib
// RUN: touch %T/lib/libLTO.dylib
// RUN: %clang -target x86_64-apple-darwin10 -### %s \
// RUN:   -ccc-install-dir %T/bin -mlinker-version=133 2> %t.log
// RUN: FileCheck -check-prefix=LINK_LTOLIB_PATH %s -input-file %t.log
//
// LINK_LTOLIB_PATH: {{ld(.exe)?"}}
// LINK_LTOLIB_PATH: "-lto_library"

// RUN: %clang -target x86_64-apple-darwin10 -### %s \
// RUN:   -ccc-install-dir %S/dummytestdir -mlinker-version=133 2> %t.log
// RUN: FileCheck -check-prefix=LINK_LTOLIB_PATH_WRN %s -input-file %t.log
//
// LINK_LTOLIB_PATH_WRN: warning: libLTO.dylib relative to clang installed dir not found; using 'ld' default search path instead

// RUN: %clang -target x86_64-apple-darwin10 -### %s \
// RUN:   -ccc-install-dir %S/dummytestdir -mlinker-version=133 -Wno-liblto 2> %t.log
// RUN: FileCheck -check-prefix=LINK_LTOLIB_PATH_NOWRN %s -input-file %t.log
//
// LINK_LTOLIB_PATH_NOWRN-NOT: warning: libLTO.dylib relative to clang installed dir not found; using 'ld' default search path instead
