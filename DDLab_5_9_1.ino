#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

#define BUTTON 2

const int row[] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
const int col[] = {COL1,COL2, COL3, COL4, COL5, COL6, COL7, COL8};

int imgIndexNow = 0;
bool isPressing = false;

int circle[8][8] = {{1,1,0,0,0,0,1,1},
                   {1,0,1,1,1,1,0,1},
                   {0,1,1,1,1,1,1,0},
                   {0,1,1,1,1,1,1,0},
                   {0,1,1,1,1,1,1,0},
                   {0,1,1,1,1,1,1,0},
                   {1,0,1,1,1,1,0,1},
                   {1,1,0,0,0,0,1,1}};

int face[8][8] = {{1,1,0,0,0,0,1,1},
                 {1,0,1,1,1,1,0,1},
                 {0,1,1,0,0,1,1,0},
                 {0,1,1,1,1,1,1,0},
                 {0,1,0,1,1,0,1,0},
                 {0,1,1,0,0,1,1,0},
                 {1,0,1,1,1,1,0,1},
                 {1,1,0,0,0,0,1,1}};
int H[8][8] = {{1,1,1,1,1,1,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,0,0,0,1,1},
		       {1,1,0,0,0,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,1,1,1,1,1,1}};

int A[8][8] = {{1,1,1,1,1,1,1,1},
		       {1,1,1,0,0,1,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,0,0,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,1,1,1,1,1,1}};          
// 其他圖案如 face2, H, A, 等...

byte incomingByte;

void setup() {
  Serial.begin(9600);

  // 設置 row 和 col 腳位
  for(byte i = 0; i < sizeof(row) / sizeof(row[0]); i++) {
    pinMode(row[i], OUTPUT);
  }
  
  for(byte i = 0; i < sizeof(col) / sizeof(col[0]); i++) {
    pinMode(col[i], OUTPUT);
  }

  // 設置按鈕腳位
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  if(Serial.available() > 0) {
    incomingByte = Serial.read();
  }

  if(incomingByte == 'c') {
    showPattern(circle);
  } 
  else if(incomingByte == 'A') {
    showPattern(A);
  }
  // 如果有更多的圖案，記得在這裡加入條件
}

void showPattern(int matrix[8][8]) {
  for(byte i = 0; i < 8; i++) {
    for(byte j = 0; j < 8; j++) {
      digitalWrite(row[i], 1 - matrix[i][j]);  // 控制 row
      digitalWrite(col[j], 1 - matrix[i][j]);  // 控制 col
    }

    // 顯示完每一行後，重置 column 狀態
    for(byte j = 0; j < 8; j++) {
      digitalWrite(col[j], LOW);  // 關閉 column
    }
  }

  // 重置所有 row 為 HIGH
  for(byte i = 0; i < 8; i++) {
    digitalWrite(row[i], HIGH); // 關閉所有 row
  }
}
