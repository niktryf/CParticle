struct particle readInitialConditions(char *filename);
void cmd_line(int argc, char *argv[], struct particle *p, struct time *t);

void printInput (struct particle p, struct time t);
double **writeToArray(double **outputArray, int n, struct particle p, double energy);
void writeFileOutput (double **outputArray, struct time t, char *filename);
