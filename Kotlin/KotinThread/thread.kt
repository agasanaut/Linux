import java.util.concurrent.locks.ReentrantLock
val lock = ReentrantLock()


fun main() {


    // Create a thread that prints a message, sleeps for 500 milliseconds, and then prints another message
    val thread = Thread {

        lock.lock() // Acquire the lock

        println("Hello from a thread!")

        Thread.sleep(500)

        println("Hello done from a thread!")

        lock.unlock() // Release the lock
    }

    // Start the thread
    thread.start()

    // Main thread continues executing
    println("Hello from the main thread!")

    // Wait for the thread to finish
    thread.join() // Wait for the thread to finish

    println("Hello done from the main thread!")

}
