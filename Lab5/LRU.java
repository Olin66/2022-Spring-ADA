import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class LRU {
    static Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String[] args) {
        int n = in.nextInt();
        int m = in.nextInt();
        HashMap<Integer, Node> map = new HashMap<>();
        LinkedList list = new LinkedList(n);
        List<Integer> result = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            String str = in.next();
            int key = in.nextInt();
            if (str.equals("put")) {
                int val = in.nextInt();
                if (map.get(key) == null) {
                    Node node = new Node(key, val);
                    map.put(key, node);
                    int del = list.add(node);
                    if (del != 0) map.remove(del);
                } else {
                    Node node = map.get(key);
                    node.val = val;
                    list.get(node);
                }
            } else if (str.equals("get")) {
                if (map.get(key) == null) result.add(-1);
                else {
                    Node node = map.get(key);
                    result.add(node.val);
                    list.get(node);
                }
            }
        }
        for (Integer i : result) out.println(i);
        out.close();
    }

    static class LinkedList {
        Node head;
        Node tail;
        int n;
        int size = 0;

        LinkedList(int n) {
            this.n = n;
        }

        int add(Node node) {
            if (this.n == 1) {
                int key = this.head == null ? 0 : this.head.key;
                this.head = node;
                this.tail = node;
                return key;
            }
            if (this.size == 0) {
                this.size++;
                this.head = node;
                this.tail = node;
            } else if (this.size == this.n) {
                this.tail.next = node;
                node.pre = this.tail;
                this.tail = node;
                this.head.next.pre = null;
                int key = this.head.key;
                this.head = this.head.next;
                return key;
            } else {
                this.tail.next = node;
                node.pre = this.tail;
                this.tail = node;
                this.size++;
            }
            return 0;
        }

        void get(Node node) {
            if (n == 1 || this.tail == node) return;
            if (node.pre != null) node.pre.next = node.next;
            if (node.next != null) node.next.pre = node.pre;
            this.tail.next = node;
            node.pre = this.tail;
            this.tail = node;
            if (node == head) {
                head = node.next;
                node.next.pre = null;
            }
            node.next = null;
        }
    }

    static class Node {
        int key;
        int val;
        Node pre;
        Node next;

        Node(int key, int val) {
            this.key = key;
            this.val = val;
        }
    }
}
