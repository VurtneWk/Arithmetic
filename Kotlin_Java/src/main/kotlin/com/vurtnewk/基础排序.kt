package com.vurtnewk

import kotlin.random.Random

/**
 * ## 冒泡排序
 *
 * 步骤&原理：
 * 1. 每次循环比较连续的两个值，把较大的进行交换到后面。每轮过后能确定一个最大值。
 * 2. 经过n轮循环后 最终排序完所有数据
 */
fun bubbleSort(arr: MutableList<Int>) {
    for (i in 0..<arr.size) {
        var swapped = false
        // 每循环一轮 参与排序的数据 少一个
        for (j in 0..<arr.size - i - 1) {
            // 如果前面一个大于后面的这个 就交换数据
            if (arr[j] > arr[j + 1]) {
                val temp = arr[j]
                arr[j] = arr[j + 1]
                arr[j + 1] = temp
                swapped = true
            }
        }
        if (!swapped) return
    }
}

/**
 * ## 选择排序
 * 步骤&原理：
 * 1. 每轮遍历所有数据，选择一个最小值，循环结束后交换放到最前面
 * 2. 经过n轮循环后 ， 最终排序完所有数据
 *
 * 效率比 冒泡高，因为交换少
 */
fun choiceSort(list: MutableList<Int>) {
    for (i in 0..<list.size) {
        var index = i
        for (j in i + 1..<list.size) {
            if (list[index] > list[j]) {
                index = j
            }
        }
        // 进行过交换
        if (index != i) {
            val oldValue = list[i]
            list[i] = list[index]// 最小值
            list[index] = oldValue
        }
    }
}

/**
 * ## 插入排序
 *
 * 步骤&原理
 * 从第二个元素开始，把前面的元素序列当作已经有序的，然后找合适的位置插入。
 *
 */
fun insertSort(list: MutableList<Int>) {
    // 从第一个元素开始
    for (i in 1..<list.size) {
        val value = list[i]// 要和前面进行比较的值
        var j = i - 1 // 前面的值的最大索引
        // 如果遇到比value大的值，就往后挪动
        while (j >= 0 && list[j] > value) {
            list[j + 1] = list[j]
            j--
        }
        // 找到位置后插入
        list[j + 1] = value
    }
}

fun main() {
    val array = mutableListOf<Int>()
    repeat(10) {
        array.add(Random.nextInt(0, 100))
    }
    println(array)
    insertSort(array)
    println(array)
}