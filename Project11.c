
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 5   // جرّب 3 أو 10

typedef struct {
    char buffer[SIZE];
    int head;     // مؤشر القراءة
    int tail;     // مؤشر الكتابة
    int count;    // عدد العناصر الحالية
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// الكتابة
void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("Buffer Overflow! لا يمكن كتابة '%c'\n", data);
        return;
    }

    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

// القراءة
char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("Buffer Underflow! لا توجد بيانات\n");
        return '\0';
    }

    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[100];

    printf("أدخل اسمك: ");
    fgets(name, sizeof(name), stdin);

    // إزالة \n
    name[strcspn(name, "\n")] = '\0';

    // نص مضاف
    char toAppend[] = "CE-ESY";

    // حماية من overflow
    if (strlen(name) + strlen(toAppend) < sizeof(name)) {
        strcat(name, toAppend);
    } else {
        printf("النص طويل جدًا!\n");
        return 1;
    }

    printf("\nالنص: %s\n", name);
    printf("حجم المخزن: %d\n", SIZE);

    int len = strlen(name);
    printf("طول النص: %d\n\n", len);

    // الكتابة
    for (int i = 0; i < len; i++) {
        write(&cb, name[i]);
    }

    printf("\n-- القراءة من المخزن --\n");

    while (!isEmpty(&cb)) {
        char ch = read(&cb);
        if (ch != '\0')
            printf("%c", ch);
    }

    printf("\n\nالمخزن فارغ (isEmpty = %d)\n", isEmpty(&cb));

    return 0;
}
