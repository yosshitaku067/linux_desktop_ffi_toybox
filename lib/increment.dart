import 'dart:ffi';
import 'dart:io';
import 'package:path/path.dart';

const DYNAMIC_LIBRARY_FILE_NAME = "libexamplers.so";

typedef IncrementRust = Int32 Function(Int32);
typedef IncrementDart = int Function(int);


int increment(int value) {
  if (!Platform.isLinux) {
    print("Dynamic library is not compatible with this platform.");
    throw Exception();
  }

  final DynamicLibrary myFuncLib = DynamicLibrary.open(
      join(Directory.current.path, 'myrustlib', DYNAMIC_LIBRARY_FILE_NAME));

  final IncrementDart increment = myFuncLib
      .lookup<NativeFunction<IncrementRust>>('increment')
      .asFunction();

  return increment(value);
}