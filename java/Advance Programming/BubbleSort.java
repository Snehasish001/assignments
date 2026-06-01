public class BubbleSort implements Sortable {
    public void sort(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            for (int j = 0; j < arr.length - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    void display(int[] arr) {
        System.out.print("Array : | ");
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]+" | ");
        }
    }


    public static void main(String[] args) {
        BubbleSort b = new BubbleSort();
        int[] arr = {10, 5, 20, 32, 1, 23, 42, 2, 1, 3, 4, 6};
        b.sort(arr);

        b.display(arr);
    }
}
