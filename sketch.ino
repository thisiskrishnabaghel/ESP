/*
  Basic calculator
  - Inputs: two (up-to-3-digit) numbers from keypad
  - A => addition
  - B => subtraction
  - C => clear (reset)
  - D => division
  - # => equals (compute)
  - * => multiplication
  - If result >= 10000 show EEEE
*/
void setup() {
  volatile char  *dirc, * dirl, *dirf, *dirk;
  dirc = 0x27; dirl = 0x10A; dirf = 0x30; dirk = 0x107;
  *dirc = 0xFF; *dirl = 0x0F; *dirf = 0x0F; *dirk = 0xF0;
}

void display_all(int res[1]) {
  volatile long p, m;
  volatile char *outc, *outl, *ink, *outf;
  outc = 0x28; outl = 0x10B; ink = 0x106; outf = 0x31;
  int key_pressed[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  int all[4] = {0, 0, 0, 0};
  int n = res[0];
  if ( n < 0) {
    n = -1 * n;
  }
  int r = 0;
  int s = 0;
  int i = 0;
  while (n != 0) {
    all[i++] = key_pressed[(n % 10)];
    n /= 10;
  }
  if (res[0] < 0) {
    all[3] = 64;
  }
  while (1) {
    //
    *outl = 0xFF;
    *outc = all[3];
    *outl = 0x07;
    //
    *outl = 0xFF;
    *outc = all[2];
    *outl = 0x0B;
    //
    *outl = 0xFF;
    *outc = all[1];
    *outl = 0x0D;
    //
    *outl = 0xFF;
    *outc = all[0];
    *outl = 0x0E;
    // }
    for ( m = 0; m < 4; m++) {
      *outf = 1 << m;
      int t = *ink;
      if (m == 2 && t == 0x08) {
        *outc = 0x00;
        while ( t & *ink);
        delay(20);
        goto ending;
      }
    }
  }
ending: *outc = 0x00;
}
//
void display_all_float(float res[1]) {
  volatile long p, m;
  volatile char *outc, *outl, *ink, *outf;
  outc = 0x28; outl = 0x10B; ink = 0x106; outf = 0x31;
  int key_pressed[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  int all[4] = {0, 0, 0, 0};
  float n = res[0];
  int one_by_hundred = (int)(res[0] * 100) % 10;
  int one_by_ten = (int)(res[0] * 10) % 10;
  int ones = (int)(res[0]) % 10;
  int tens = (int)(res[0] / 10) % 10;
  all[0] = key_pressed[one_by_hundred];
  all[1] = key_pressed[one_by_ten];
  all[2] = key_pressed[ones];
  all[3] = key_pressed[tens];
  while (1) {
    //
    *outl = 0xFF;
    *outc = all[3];
    *outl = 0x07;
    //
    *outl = 0xFF;
    *outc = all[2] | 0x80;
    *outl = 0x0B;
    //
    *outl = 0xFF;
    *outc = all[1];
    *outl = 0x0D;
    //
    *outl = 0xFF;
    *outc = all[0];
    *outl = 0x0E;
    // }
    for ( m = 0; m < 4; m++) {
      *outf = 1 << m;
      int t = *ink;
      if (m == 2 && t == 0x08) {
        *outc = 0x00;
        while ( t & *ink);
        delay(20);
        goto ending;
      }
    }
  }
ending: *outc = 0x00;
}

//
void out_of_bound(int res[1]) {
  volatile long p, m;
  volatile char *outc, *outl, *ink, *outf;
  outc = 0x28; outl = 0x10B; ink = 0x106; outf = 0x31;
  int key_pressed[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  int all[4] = {0x79, 0x79, 0x79, 0x79};
  while (1) {
    //
    *outl = 0xFF;
    *outc = all[3];
    *outl = 0x07;
    //
    *outl = 0xFF;
    *outc = all[2];
    *outl = 0x0B;
    //
    *outl = 0xFF;
    *outc = all[1];
    *outl = 0x0D;
    //
    *outl = 0xFF;
    *outc = all[0];
    *outl = 0x0E;
    // }
    for ( m = 0; m < 4; m++) {
      *outf = 1 << m;
      int t = *ink;
      if (m == 2 && t == 0x08) {
        *outc = 0x00;
        while ( t & *ink);
        delay(20);
        goto ending;
      }
    }
  }
ending: *outc = 0x00;
}

void sum_up( int digits[2][3], int digi_track[2]) {
  int res[1] = {0x00};
  int num1 = 0;
  int num2 = 0;
  int digi1 = digi_track[0];
  int digi2 = digi_track[1];
  digi_track[0] = 0x00;
  digi_track[1] = 0x00;
  int num = 0;
  for (int m = 0; m < digi1; m++ ) {
    num1 = num1 * 10 ;
    num1 = digits[0][m] + num1 ;
  }
  for (int m = 0; m < digi2; m++ ) {
    num2 = num2 * 10 ;
    num2 = digits[1][m] + num2 ;
  }
  res[0] = num1 + num2;
  display_all(res);
}
//

void subtract( int digits[2][3], int digi_track[2]) {
  int res[1] = {0x00};
  int num1 = 0;
  int num2 = 0;
  int digi1 = digi_track[0];
  int digi2 = digi_track[1];
  digi_track[0] = 0x00;
  digi_track[1] = 0x00;
  int num = 0;
  for (int m = 0; m < digi1; m++ ) {
    num1 = num1 * 10 ;
    num1 = digits[0][m] + num1 ;
  }
  for (int m = 0; m < digi2; m++ ) {
    num2 = num2 * 10 ;
    num2 = digits[1][m] + num2 ;
  }
  res[0] = num1 - num2;
  display_all(res);
}
//

void do_multiply( int digits[2][3], int digi_track[2]) {
  int res[1] = {0x00};
  int num1 = 0;
  int num2 = 0;
  int digi1 = digi_track[0];
  int digi2 = digi_track[1];
  digi_track[0] = 0x00;
  digi_track[1] = 0x00;
  int num = 0;
  for (int m = 0; m < digi1; m++ ) {
    num1 = num1 * 10 ;
    num1 = digits[0][m] + num1 ;
  }
  for (int m = 0; m < digi2; m++ ) {
    num2 = num2 * 10 ;
    num2 = digits[1][m] + num2 ;
  }
  res[0] = num1 * num2;
  if ( res[0] < 9999) {
    display_all(res);
  }
  else {
    out_of_bound(res);
  }
}
//
void do_divide( int digits[2][3], int digi_track[2]) {
  float res[1] = {0x00};
  float num1 = 0;
  float num2 = 0;
  int digi1 = digi_track[0];
  int digi2 = digi_track[1];
  digi_track[0] = 0x00;
  digi_track[1] = 0x00;
  int num = 0;
  for (int m = 0; m < digi1; m++ ) {
    num1 = num1 * 10.0 ;
    num1 = digits[0][m] + num1 ;
  }
  for (int m = 0; m < digi2; m++ ) {
    num2 = num2 * 10.0 ;
    num2 = digits[1][m] + num2 ;
  }
  res[0] = num1 / num2;
  int check = (res[0] - (int) res[0]) * 100;
  display_all_float(res);
}
void loop() {
  static int shift = 0;
  static int a = 0;
  static int b = 0;
  static int multi = 0;
  static int div = 0;
  volatile char *outa, *outb, *outc, * outl, *outf, *ink;
  outa = 0x22; outb = 0x25 ; outc = 0x28; outl = 0x10B; outf = 0x31; ink = 0x106;
  int key_pressed[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
  static int array_select = 0;
  int partial_show[2][3] = {{0x00, 0x00, 0x00}, {0x00, 0x00, 0x00}};
  int digits[2][3] ;
  static int digi_track[2] = {0x00, 0x00};
  volatile long i, j = 0;
next_array: int pos1 = 0, pos2 = 0, key_value;
  while (pos1 < 3) {
    for ( i = 0; i < 4; i++) {
      *outf = 1 << i;
      int t = *ink;
      if (t != 0) {
        delay(200);
        while ((*ink & t) == t);
        delay(20);
        if (*outf == 0x01) {
          if (t == 0x01) key_value = 0x06;
          else if (t == 0x02) key_value = 0x5B;
          else if (t == 0x04) key_value = 0x4F;
          else {
            array_select++;
            shift = 0;
            a = 1;
            // Serial.println(array_select);
            if ( array_select == 2) {
              goto time_to_add;
            }
            goto next_array;
          }
        }
        else if (*outf == 0x02) {
          if (t == 0x01) key_value = 0x66;
          else if (t == 0x02) key_value = 0x6D;
          else if (t == 0x04) key_value = 0x7D;
          else  {
            array_select++;
            shift = 0;
            b = 1;
            // Serial.println(array_select);
            if ( array_select == 2) {
              goto time_to_subtract;
            }
            goto next_array;
          }
        }
        else if (*outf == 0x04) {
          if (t == 0x01) key_value = 0x07;
          else if (t == 0x02) key_value = 0x7F;
          else if (t == 0x04) key_value = 0x6F;
          else key_value = 0x39;
        }
        else {
          if (t == 0x01) {
            array_select++;
            shift = 0;
            multi = 1;
            // Serial.println(array_select);
            if ( array_select == 2) {
              goto time_to_multiply;
            }
            goto next_array;
          }
          else if (t == 0x02) key_value = 0x3F;
          else if (t == 0x04)
          {
            // this was for the case when # is pressed but it will work in case
            // when less than 3 digits are entered
            array_select++;
            shift = 0;
            // Serial.println(array_select);
            if ( array_select == 2 && a == 1) {
              // a = 1;
              goto time_to_add;
            }
            if ( array_select == 2 && b == 1) {
              //b = 1;
              goto time_to_subtract;
            }
            if ( array_select == 2 && multi == 1) {
              // multiply = 1;
              goto time_to_multiply;
            }
            if ( array_select == 2 && div == 1) {
              // div = 1;
              goto time_to_divide;
            }
          }
          else {
            array_select++;
            shift = 0;
            div = 1;
            // Serial.println(array_select);
            if ( array_select == 2) {
              goto time_to_divide;
            }
            goto next_array;
          }
        }

        partial_show[array_select][pos1++] = key_value;
        for ( int w = 0 ; w < 10; w++) {
          if ( key_value == key_pressed[w])
          { digits[array_select][pos2++] = w;
            digi_track[array_select]++;
            break;
          }
        }
        shift++;
        if (pos1 == 3) break;
      }
    }

never: for ( int temp_shift = shift, s = 0; temp_shift > 0 && s < 3 ; temp_shift--, s++) {
      *outl = 0xFF;
      *outc = partial_show[array_select][s];
      *outl = (0x0F & (~(1 << (temp_shift - 1))));
      *outc = 0x00;
    }
    if ( pos1 == 3) {
      for (int m = 0; m < 4; m++) {
        *outf = 1 << m;
        int temp = *ink;
        // delay(100);
        while ((*ink & temp));
        delay(20);
        if ((m == 0 && temp == 0x08) ) {
          if ( array_select == 0) {
            a = 1;
          }
          array_select++;
          goto ktm_add;
        }
        //
        if ((m == 1 && temp == 0x08) ) {
          if ( array_select == 0) {
            b = 1;
          }
          array_select++;
          goto ktm_subtract;
        }
        if ((m == 3 && temp == 0x01) ) {
          if ( array_select == 0) {
            multi = 1;
          }
          array_select++;
          goto ktm_multiply;
        }
        if ((m == 3 && temp == 0x08) ) {
          if ( array_select == 0) {
            div = 1;
          }
          array_select++;
          goto ktm_divide;
        }
        // equal button logic below
        if ((m == 3 && temp == 0x04) && a == 1) {
          //a = 1;
          array_select++;
          goto ktm_add;
        }
        if ((m == 3 && temp == 0x04) && b == 1) {
          // b = 1;
          array_select++;
          goto ktm_subtract;
        }
        if ((m == 3 && temp == 0x04) && multi == 1) {
          //multi = 1;
          array_select++;
          goto ktm_multiply;
        }
        if ((m == 3 && temp == 0x04) && div == 1) {
          //div = 1;
          array_select++;
          goto ktm_divide;
        }
      }
      goto never;
    }
  }//
ktm_add: {
time_to_add: if ( array_select == 2 && a == 1)
    { a = 0;
      shift = 0;
      array_select = 0;
      sum_up(digits, digi_track);
    }
    shift = 0;
    *outc = 0x00;
  }
  //
ktm_subtract: {
time_to_subtract: if ( array_select == 2 && b == 1)
    { b = 0;
      shift = 0;
      array_select = 0;
      subtract(digits, digi_track);
    }
    shift = 0;
    *outc = 0x00;
  }
ktm_multiply: {
time_to_multiply: if ( array_select == 2 && multi == 1)
    { multi = 0;
      shift = 0;
      array_select = 0;
      do_multiply(digits, digi_track);
    }
    shift = 0;
    *outc = 0x00;
  }
ktm_divide: {
time_to_divide: if ( array_select == 2 && div == 1)
    { div = 0;
      shift = 0;
      array_select = 0;
      do_divide(digits, digi_track);
    }
    shift = 0;
    *outc = 0x00;
  }

}