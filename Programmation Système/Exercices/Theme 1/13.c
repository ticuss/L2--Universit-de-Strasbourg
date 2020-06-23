int factorielle(int n) {
  int f;
  if (n <= 1)
    f = 1;
  else
    f = n * factorielle(--n); // comme le dit le warning, rien ne garantit que le -- soit fait après le n*
  return f;
}
