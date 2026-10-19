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
cmake --preset=default
./build/spectogram
```
