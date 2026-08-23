import '/common.dart';
import '/utility/storage_path.dart';
import '/bridge/service.dart';
import 'dart:ffi' as lib;

// ----------------

class Library {

  // #region constructor

  lib.DynamicLibrary? _handle;

  lib.Pointer<Service>? _symbol;

  // ----------------

  Library(
  ) :
    this._handle = null,
    this._symbol = null;

  // #endregion

  // #region access

  Boolean state(
  ) {
    return this._handle != null;
  }

  // ----------------

  Void open(
    StoragePath path,
  ) {
    assertTest(!this.state());
    var pathString = path.emitNative();
    if (SystemChecker.isWindows) {
      pathString += '.';
    }
    this._handle = lib.DynamicLibrary.open(pathString);
    try {
      this._symbol = this._handle!.lookup<Service>('_ZN8Twinning6Kernel9Interface7serviceE');
      this._symbol!.ref.initialize.asFunction<Void Function()>()();
    }
    catch (e) {
      this._symbol = null;
      this._handle!.close();
      this._handle = null;
      rethrow;
    }
    return;
  }

  Void close(
  ) {
    assertTest(this.state());
    this._symbol!.ref.finalize.asFunction<Void Function()>()();
    this._symbol = lib.nullptr;
    this._handle!.close();
    this._handle = null;
    return;
  }

  // ----------------

  Service symbol(
  ) {
    assertTest(this.state());
    return this._symbol!.ref;
  }

  // #endregion

}
