file(REMOVE_RECURSE
  "libtriangle.pdb"
  "libtriangle.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/triangle.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
