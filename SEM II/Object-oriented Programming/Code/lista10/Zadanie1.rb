# Piotr Stachowicz zadanie 1 lista 10
class Collection
  def initialize(que)
    @queue = que
  end
  def length
    @queue.length
  end
  def get(i)
    @queue[i]
  end
  def set(i, x)
    @queue[i] = x
  end
  def swap(i, j)
    x = @queue[i]
    y = @queue[j]
    set(i,y)
    set(j,x)
  end
  def add(x)
    @queue.append(x)
  end
  def pop
    @queue.pop
  end
  def pprint
    print @queue
  end
  def get_queue
    @queue
  end
end
class Sorter
  def sort1(kolekcja)
    # bubble sort
    n = kolekcja.length
    for i in 0..n-1
      for j in 1..n-i-1
        if kolekcja.get(j-1) > kolekcja.get(j)
          kolekcja.swap(j-1,j)
        end
      end
    end
  end
  def sort2(kolekcja)
    # ta metoda sortowania jest szybsza
    mergeSort(kolekcja.get_queue)
  end
  def mergeSort(arr)
    if arr.length < 2
      return arr
    end
    mid = arr.length/2
    left = arr.slice(0,mid)
    right = arr.slice(mid,arr.length)
    mergeSort(left)
    mergeSort(right)
    return merge(arr, left, right)
  end

  def merge(arr, left, right)
    i = j = k = 0
    left_len = left.length
    right_len = right.length
    while i < left_len and j < right_len
      if left[i] < right[j]
        arr[k] = left[i]
        i += 1
      else
        arr[k] = right[j]
        j += 1
      end
      k += 1
    end
    while i < left_len
      arr[k] = left[i]
      i += 1
      k += 1
    end
    while j < right_len
      j += 1
      k += 1
    end
    return arr
  end
end
x = Sorter.new
y = Collection.new([9,2,1,8,7,4,3])
x.sort2(y)
y.pprint