#include <bits/stdc++.h>
using namespace std;

void build(int index, int low, int high, int arr[], int seg[]) {
  if (low == high) {
    seg[index] = arr[low];
    return;
  }
  int mid = (low + high) / 2;
  build(2 * index + 1, low, mid, arr, seg);
  build(2 * index + 2, mid + 1, high, arr, seg);
  seg[index] = seg[2 * index + 1] + seg[2 * index + 2];
}

int query(int index, int low, int high, int l, int r, int seg[]) {
  // no overlap
  // l r low high  or low high l r 
  if (r < low || high < l)
    return 0;

  //complete overlap
  // l low high r
  if (low >= l && high <= r)
    return seg[index];

  int mid = (low + high) / 2;
  int left = query(2 * index + 1, low, mid, l, r, seg);
  int right = query(2 * index + 2, mid + 1, high, l, r, seg);

  return left + right;
}

void update(int index, int low, int high, int i, int val, int seg[]) {
  if (low == high) {
    seg[index] = val;
    return;
  }

  int mid = (low + high) / 2;
  if (i <= mid) update(2 * index + 1, low, mid, i, val, seg);
  else update(2 * index + 2, mid + 1, high, i, val, seg);
  seg[index] = seg[2 * index + 1] + seg[2 * index + 2];
}

void solve() {
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) cin >> arr[i];

  int seg[4 * n];
  build(0, 0, n - 1, arr, seg);

  int q;
  cin >> q;
  while (q--) {
    int type;
    cin >> type;
    if (type == 1) {
      int l, r;
      cin >> l >> r;
      cout << query(0, 0, n - 1, l, r, seg) << endl;
    } else {
      int i, val;
      cin >> i >> val;
      update(0, 0, n - 1, i, val, seg);
      arr[i] = val;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  solve();
  return 0;
}