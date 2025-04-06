fun main() {
    println("Hello, Kotlin on Ubuntu!")
}



/*
How to run this code???

1. Install Kotlin on Ubuntu:
   - Open a terminal and run the following command to install Kotlin:
     ```bash
     sudo snap install kotlin --classic
     ```
   - Alternatively, you can install Kotlin using SDKMAN!:
     ```bash
     curl -s "https://get.sdkman.io" | bash
     source "$HOME/.sdkman/bin/sdkman-init.sh"
     sdk install kotlin
     ```                                                        .



2. Create a Kotlin file:



    - Open a terminal and create a new Kotlin file named `hello.kt`:
      ```bash
      nano hello.kt
      ```
    - Copy and paste the above code into the `hello.kt` file.
    - Save and exit the editor (in nano, press `CTRL + X`, then `Y`, then `Enter`). 

3. Compile the Kotlin file:
   - In the terminal, run the following command to compile the Kotlin file:
     ```bash
     kotlinc hello.kt -include-runtime -d hello.jar
     ```                                                                
    - This command compiles the `hello.kt` file and creates a JAR file named `hello.jar` that includes the Kotlin runtime.          

4. Run the Kotlin program:
   - In the terminal, run the following command to execute the Kotlin program:
     ```bash
     java -jar hello.jar
     ```
   - You should see the output:
     ```
     Hello, Kotlin on Ubuntu!
     ```
5. Clean up:
   - You can delete the `hello.kt` and `hello.jar` files if you no longer need them:
     ```bash
     rm hello.kt hello.jar
     ```
6. Additional Resources:
   - [Kotlin Documentation](https://kotlinlang.org/docs/home.html)
   - [Kotlin on Ubuntu](https://kotlinlang.org/docs/command-line.html#ubuntu)
   - [Kotlin Snap Package](https://snapcraft.io/kotlin)
   - [SDKMAN!](https://sdkman.io/)          



*/