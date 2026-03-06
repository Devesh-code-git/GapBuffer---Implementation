public class GapBuffer {
    private char[] line = new char[50];
    private int cursor = 0;
    private int gap_end = line.length - 1;
    private int gap_size;


    public static void main(String args[]) {
        GapBuffer g = new GapBuffer();
    }

    GapBuffer() {}

    public void insert(char c) {
        gap_size = gap_end - this.cursor;

        if (gap_size <= 0) {
            this.resize();
        }

        line[this.cursor] = c;
        this.cursor++;
        gap_size = gap_end - this.cursor;
    }

    public void remove() {
        if (!(this.cursor <= 0)) {
            this.cursor--;
            line[this.cursor] = '\u0000';
        }
    }

    public void left() {
        char c;

        if (this.cursor != 0) {
            c = line[this.cursor - 1]; // Save the character before the start of the gap

            // Move start of and end of gap leftwards
            this.cursor--;
            gap_end--;
            gap_size = gap_end - this.cursor;

            line[this.cursor] = '\u0000'; // Put the empty chracter at the new start of the gap
            line[gap_end + 1] = c; // Put saved character at end of the gap
        }
    }

    public void right() {
        char c;

        if (gap_end != line.length - 1) {
            c = line[gap_end + 1]; // Save the character thats after the end of the gap

            // Move start of and end of gap rightwards
            this.cursor++;
            gap_end++;
            gap_size = gap_end - this.cursor;

            line[gap_end] = '\u0000';
            line[this.cursor - 1] = c;
        }
    }

    public void show() {
        System.out.println("");
        for (int i = 0; i < line.length; i++){
            if (line[i] != '\u0000') {
                System.out.print(line[i]);
            } else {
                System.out.print("_");
            }
        }
        System.out.println();
    }

    private void resize() {
        int size = line.length;
        char[] new_arr = new char[size*2];

        for (int i = 0; i < line.length; i++) {
            new_arr[i] = line[i];
        }

        line = new_arr; // Set original array to new_array that has been allocated with original arrays contents

        gap_end = new_arr.length - 1; // Make the end of the gap the end of the new array
        gap_size = gap_end - this.cursor; // Recalculate size of the gap
    }
}