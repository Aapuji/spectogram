# Thoughts
Use a produce-consumer model. 
- One thread is interfacing with audio and reading it, outputting to a circular buffer.
- Either another thread or the same thread is doing windowing, FFT, converting to DB, and pushing result to a queue
- The final thread is for visualizing the result, likely at 60 fps.

Apparently it is bad to allocate memory inside the audio loop will cause stutters. Instead I should be re-using fixed-size buffers.
Also make sure queues have a max capacity.

As of now, idea is to use
- RTAudio
- FFTW
- SFML

# Fixing vcpkg installation
Need to put all feature information in `vcpkg.json`. Then use `vcpkg install` in terminal.

Then
```sh
cmake --preset vcpkg # only if CMakeLists or other stuff has changed
cmake --build build
./build/spectogram
```
# Experiences with `cmake`, `vcpkg`
Make sure `$env:VCPKG_ROOT` is set.
Once I finally got it to compile, it still wasn't linking. The status code is `-1073741515` which is `STATUS_DLL_NOT_FOUND`. Causes:
- `CMakePresets.json` was using the classic `mingw64` compiler branch (`msvcrt.dll`), while system paths and dependencies were pulling from the modern `ucrt64` branch (`ucrtbase.dll`). This broke underlying child modules.
- `vcpkg`'s automated DLL copying (`VCPKG_APPLOCAL_DEPS`) failed because it is primarily optimized for `MSVC`, leaving the build directory empty of runtime binaries.
Solution:
- Unified the Toolchain: Switched the compiler in `CMakePresets.json` to the modern Universal C Runtime path to match the `x64-mingw-dynamic` `vcpkg` triplet.
- Explicit Linking: Updated `CMakeLists.txt` to explicitly link `SFML` components directly to the executable target (`spectogram`) rather than relying solely on the static library (`spectogram_lib`).
