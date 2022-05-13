import java.io.*;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

public class StableMatching {
    static Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) {
        int N = in.nextInt();
        HashMap<String, Person> boyName = new HashMap<>();
        Person[] boys = new Person[N];
        HashMap<String, Person> girlName = new HashMap<>();
        Person[] girls = new Person[N];
        Queue<Person> queue = new LinkedList<>();
        for (int i = 0; i < N; i++) {
            String name = in.next();
            Person boy = new Person(name, i, 0, N);
            boyName.put(name, boy);
            boys[i] = boy;
            queue.add(boy);
        }
        for (int i = 0; i < N; i++) {
            String name = in.next();
            Person girl = new Person(name, i, 1, N);
            girlName.put(name, girl);
            girls[i] = girl;
        }
        for (int i = 0; i < N; i++) {
            Person boy = boys[i];
            for (int j = 0; j < N; j++) {
                String target = in.next();
                Person girl = girlName.get(target);
                boy.pref[j] = girl.no;
            }
        }
        for (int i = 0; i < N; i++) {
            Person girl = girls[i];
            for (int j = 0; j < N; j++) {
                String target = in.next();
                Person boy = boyName.get(target);
                girl.pref[j] = boy.no;
            }
            girl.inverse = new int[N];
            for (int j = 0; j < N; j++) {
                girl.inverse[girl.pref[j]] = j;
            }
        }
        while (!queue.isEmpty()) {
            Person boy = queue.peek();
            if (boy.count == N) queue.poll();
            Person girl = girls[boy.pref[boy.count]];
            if (girl.couple == -1) {
                girl.couple = boy.no;
                queue.poll();
                boy.count++;
                boy.couple = girl.no;
            } else if (girl.inverse[boy.no] < girl.inverse[girl.couple]) {
                Person loser = boys[girl.couple];
                queue.add(loser);
                girl.couple = boy.no;
                queue.poll();
                boy.count++;
                boy.couple = girl.no;
            } else boy.count++;
        }
        out.println();
        for (Person boy : boys) {
            out.println(boy + " " + girls[boy.couple]);
        }
        out.close();
    }

    static class Person {
        String name;
        int no;
        int gender;//0 for male, 1 for female
        int[] pref;
        int[] inverse;
        int count = 0;
        int couple = -1;

        Person(String name, int no, int gender, int N) {
            this.name = name;
            this.no = no;
            this.gender = gender;
            pref = new int[N];
        }

        @Override
        public String toString() {
            return this.name;
        }
    }
}