package com.company;

import java.util.Scanner;


public class Main {

    /*
     * Variables to track the largest number of divisors and its corresponding number
     * These are set as volatile because updates of one thread is not visible by
     * another thread in memory.
     * Volatile guarantees visibility immediately to other threads
     */
    public volatile static int maxDivisorsCount = 0;
    public volatile static int numberWithMaxDivisors = 0;


    /*
     * The main method will retrieve the number of cores that is available to the JCM
     * The user is given an option to utilize 1 core or all cores provided
     * Note: The range is hardcoded for the purpose of this assignment
     */
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int cores = Runtime.getRuntime().availableProcessors();
        int preferredCores = 1;
        int range = 10000;

        System.out.println("You have " + cores + " cores avaiable. Test with (A) 1 core or (B) " +cores +" cores?");
        String result = input.next().toUpperCase();

        if(result.equals("A")){
            preferredCores = 1;
        } else if(result.equals("B")){
            preferredCores = 12;
        } else {
            System.out.println("Unknown input. Testing with " +cores+ " core");
        }

        System.out.println("\nCalculating divisor of " +range+ " ints with " +preferredCores+ " threads");
        countDivisorNumbers(range, preferredCores);
    }


    /*
     * (Note: The Static keyword is used to provide class level access to a method)
     * -----------------------------------------------
     * This method is responsible for creating and running the threads based on inputted range
     * and thread size by the user
     */
    public static void countDivisorNumbers(int range, int numOfThreads){

        long startTime = System.currentTimeMillis();

        /*
         * In this part, MultithreadingDivisorCount objects are created in an array that is the size of
         * the thread. Each object represents a group of numbers from the total range based on threads used
         * Check below for the implementation of the MultithreadingDivisorCount class
         */
        MultithreadingDivisorCount[] multithreadingDivisorCount = new MultithreadingDivisorCount[numOfThreads];
        int rangePerThread = range / numOfThreads; // Group sizes
        int start = 1;  // Initially, start at number 1
        int end = rangePerThread;

        for(int i=0; i<numOfThreads; i++) {
            multithreadingDivisorCount[i] = new MultithreadingDivisorCount(start, end);
            start = end + 1; // Start with the previous group size
            end =  start + (rangePerThread - 1); // calculate next ending group size
        }


        /*
         * Once we are done grouping the MultithreadingDivisorCount objects with different ranges,
         * we can begin to start the thread.
         */
        for(int i=0; i<numOfThreads; i++){
            multithreadingDivisorCount[i].start();
        }

        /*
         * After starting all the threads, we must wait for the threads to die. The join() methods
         * allow this by waiting for each thread to complete its execution. We can also ensure that
         * the join methods execute in order
         */
        for (int i = 0; i < numOfThreads; i++) {
            try {
                multithreadingDivisorCount[i].join();
            }
            catch (InterruptedException e) {
            }
        }

        /*
         * At this point, the threads have all successfully executed and we will now get the amount
         * of time it took to complete. The results are also displayed to the user
         */
        long endTime = System.currentTimeMillis() - startTime;
        System.out.println("----------- Results ----------------");
        System.out.println(range + " numbers were tested with " +numOfThreads+ " threads");
        System.out.println("The number " + numberWithMaxDivisors + " has the largest divisor of " + maxDivisorsCount);
        System.out.println("Total time: " + (endTime/1000.0) + " seconds\n");


    }


    /**
     * (Note: A Nested class is used to logically group classes used for similar purposes.
     * The Static keyword means that the class belongs specifically to outer class. It can be
     * called without instantiating the outer class)
     * -----------------------------------------------
     * This class begins with start and end integers for a range of numbers declared in its constructor
     * The class extends Thread which allows it to be called using start() and begins execution
     * of the run() method. Once the highest divisor and number is retrieved, the results are set to the
     * static variables declared in the beginning of the Main class
     */
    public static class MultithreadingDivisorCount extends Thread {
        int start, end;

        public MultithreadingDivisorCount(int start, int end){
            this.start = start;
            this.end = end;
        }

        /*
         * Count the number of divisors for each integer
         * If the number evenly divides, then it has a divisor
         */
        public int countLargestDivisors(int number) {
            int divisorCount = 0;
            for (int i = 1; i <= number ; i++) {
                if ( number % i == 0 )
                    divisorCount ++;
            }
            return divisorCount;
        }


        /**
         * This is the thread. It compares every number that is passed through the constructors start/end
         * range and passes it to countDivisors() which will get the divisors for that number. Similar to
         * finding min/max operation of two numbers, this finds the max number with the most divisor and sets
         * it to the static variable
         */
        public void run() {
            int largestDivisor = 0;
            int largestDivisorValue = 0;
            for (int i = start; i < end; i++) {
                int divisors = countLargestDivisors(i);
                if (divisors > largestDivisor) {
                    largestDivisor = divisors;
                    largestDivisorValue = i;
                }
            }
            // Compares the largest
            if (largestDivisor > maxDivisorsCount) {
                maxDivisorsCount = largestDivisor;
                numberWithMaxDivisors = largestDivisorValue;
            }
        }

    }


}