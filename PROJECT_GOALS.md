## Learning objectives implemented

- ✅ Uses cmake for build.
- ✅ README with instructions and build info.
- ✅ Uses a variety of looping functions, including specialized helpers for mapping over lists like `for_each_in` and `find_if`.
- ✅ Program reads and writes data to a file-based database (sqlite).
- ✅ Program accepts user input and stops or continues based on input.
- ✅ OOP used with initializer, public & private members.
- ✅ Libraries like Ncurses abstracted behind class interface, encapsulating behaviour.
- ✅ Generalization with the user of templates.
- ✅ some values are passed by reference.
- ✅ Rule of 5 implement in game class.
- ✅ Move semantics and smart pointer used with player class.

## Challenges & Failures

- ❌ I spent more time on trying to implement a generic resource class than anything else. The idea was I woudld then extend it with a custom sqlite interface. This bogged down in some very difficult type errors and compilation errors that ended up being so time consuming I abandoned my efforts and turned to an ORM.
- ❌ I spent quite a lot of time trying to use a library called FunctionalPlus to implement some more functional style code, but I ran into lots of issues with compiling despite trying multiple methods.
- ❌ Ncurses brought many headaches. Many of the features seem not work on my mac terminal--colors, key constants, certain functions. Moreover I spent a lot of time trying to use a smart pointer for Ui class but after much frustration realized issues with Ncurses made this very tricky. Had I time to do it over again, I would have used the suggested library.
- ❌ I did not look at other snake examples and learning materials. In retrospect, I could have benefitted a lot from some basic principles of game design.
- ❌ I looked for ways to use concurrency, but it just didn't seem to really have a place in the sort of project I made.


