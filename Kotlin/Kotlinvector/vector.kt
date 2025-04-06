


fun main() {

    val list = mutableListOf(1, 2, 3, 4,2, 5)
    list.add(6)
    list.removeAll{it  == 2}
    println(list) 



    if(3 in list) {
        println("3 is in the list")
    } else {
        println("3 is not in the list")
    }

}