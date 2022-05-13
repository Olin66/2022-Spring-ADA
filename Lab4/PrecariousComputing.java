import java.io.*;
import java.util.Scanner;

public class PrecariousComputing {
    static Scanner in = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
    static int maxn = 100005;
    static Value[] values = new Value[maxn];
    static Value[][] st = new Value[maxn][21];
    static long[] A = new long[maxn];
    static int[] B = new int[maxn];
    static PriorityQueue pq = new PriorityQueue(maxn);

    public static void main(String[] args) {
        int n = in.nextInt();
        long m = in.nextLong();
        values[0] = new Value();
        for (int i = 1; i <= n; i++) A[i] = in.nextLong();
        for (int i = 1; i <= n; i++) B[i] = in.nextInt();
        for (int i = 1; i <= n; i++) values[i] = new Value(i);
        init(n);
        long income = 0;
        long count = 0;
        pq.add(new Interval(1, n));
        while (!pq.isEmpty()) {
            Interval sub = pq.poll();
            int l = sub.l;
            int r = sub.r;
            Value value = rmq(l, r);
            long min = value.a;
            int i = value.no;
            if (count + (min - sub.base) >= m) {
                income = income + (m - count) * sum(l, r);
                break;
            } else {
                income = income + (min - sub.base) * sum(l, r);
                count += (min - sub.base);
            }
            if (l != r) {
                Interval left = new Interval(l, i - 1);
                Interval right = new Interval(i + 1, r);
                left.base = min;
                right.base = min;
                pq.add(left);
                pq.add(right);
            }
        }
        out.println(income);
        out.close();
    }

    static Value min(Value v1, Value v2) {
        return v1.a < v2.a ? v1 : v2;
    }

    static void init(int n) {
        for (int i = 1; i <= n; i++) st[i][0] = values[i];
        for (int j = 1; j <= 20; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    static long sum(int l, int r) {
        return values[r].sum - values[l - 1].sum;
    }

    static Value rmq(int l, int r) {
        int k = (int) (Math.log(r - l + 1) / Math.log(2));
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }

    static class Value {
        int no;
        long a;
        int b;
        long sum = 0;

        Value() {

        }

        Value(int no) {
            this.no = no;
            this.a = A[no];
            this.b = B[no];
            this.sum = values[no - 1].sum + this.b;
        }
    }

    static class Interval {
        int l;
        int r;
        long sum;
        long base = 0;

        Interval(int l, int r) {
            this.l = l;
            this.r = r;
            this.sum = sum(l, r);
        }
    }

    static class PriorityQueue {
        int size;
        int capacity;
        Interval[] array;

        PriorityQueue(int n) {
            array = new Interval[n + 1];
            size = 0;
            capacity = n;
        }

        void add(Interval val) {
            size++;
            array[size] = val;
            siftUp(size);
        }

        Interval poll() {
            Interval temp = array[1];
            array[1] = array[size];
            array[size--] = array[1];
            siftDown();
            return temp;
        }

        boolean isEmpty() {
            return this.size == 0;
        }

        boolean compare(Interval a, Interval b) {
            return a.sum > b.sum;
        }

        void siftUp(int n) {
            while (n > 1 && compare(array[n], array[n >> 1])) {
                Interval temp = array[n];
                array[n] = array[n >> 1];
                array[n >> 1] = temp;
                n >>= 1;
            }
        }

        void siftDown() {
            int n = 1;
            while (2 * n <= size) {
                int k = 2 * n;
                if (k < size && compare(array[k + 1], array[k])) k++;
                if (compare(array[k], array[n])) {
                    Interval temp = array[n];
                    array[n] = array[k];
                    array[k] = temp;
                    n = k;
                } else break;
            }
        }
    }
}