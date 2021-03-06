int inputTooLarge(char* input, int limit){
    /*
     * We use fgets to get the user input. If 499th character is not a newline or null terminator, then the
     * input is larger than the 500 byte buffer (499th must be a null terminator).
     *
     * @param input String that's to be tested
     * @param limit Maximum string length
     * @return boolean value
     */
    char lastChar = input[limit - 2];
   if (lastChar == '\n' || lastChar == '\0'){
       return 0;
   } else {
       return 1;
   }
}