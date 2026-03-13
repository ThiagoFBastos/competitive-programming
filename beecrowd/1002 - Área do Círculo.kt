import java.util.*

import java.util.Locale
import kotlin.math.pow

fun area(radius: Double): Double = radius.pow(2) * 3.14159

fun main(args: Array<String>) {

	val radius = readLine()!!.toDouble()

    println("A=%.4f".format(Locale.US, area( radius)))
}