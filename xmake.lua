target("test.out")
	add_files("test/*.cpp")
	set_kind("binary")
	set_languages("c++20")
	add_links("fmt")
	add_cxflags("-O2")