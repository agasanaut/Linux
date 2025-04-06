fun main(){
    println("This is a Kotlin program.")

    //crte a class
    val obj : myclass = myclass()
    obj.myMethod()



    //inheritance
    val obj2 : vehicle = car()
    obj2.displayInfo()
}

class myclass{
    internal fun myMethod() {
        println("This is a method in myclass.")
        myMethod2()
    }

    private fun myMethod2() {
        println("This is another method in myclass.")
    }
}



open class vehicle{
    private var name: String = ""
    protected var color: String = "red"
    private var year: Int = 0

    open fun displayInfo() {
        println("Vehicle Name: $name")
        println("Vehicle Color: $color")
        println("Vehicle Year: $year")
    }
    private fun start() {
        println("$name is starting.")
    }
    private fun stop() {
        println("$name is stopping.")
    }
}

class car : vehicle() {
    override fun displayInfo() {
        println("Car color-------->: $color")
    }
}