# OpenAL Candle Plugin

## Licensing

It is a major goal of the Candle engine that its plugins require as little file dependencies outside the executable itself, for this reason, static linking is usually preferred to dynamic linking.

This plugin uses OpenAL-soft, which is licensed under LGPL, this means that if it is used in closed source software, the ability to swap it for another implementation of OpenAL must be given to the users of the software, which means static linking is out of the question.

To keep things clean, and not require a dynamic library file to be strung around with the executable, possibly breaking the software if something happens to it, the `so` or `dll` file is embedded inside the executable, but the user retains the ability to change it for another implementation because before loading the embedded file, this plugin checks if there is a dynamic library file in the directory of the executable. This means the user can swap implementations by placing his desired version of `OpenAL32.so` or `OpenAL32.dll` next to the executable.
