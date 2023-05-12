# Piotr Stachowicz zadanie 2 lista 10
class Node
  def initialize(prev_elem,elem,next_elem)
    @prev_elem = prev_elem
    @elem = elem
    @next_elem = next_elem
  end
  def set_next(x)
    @next_elem = x
  end
  def set_prev(x)
    @prev_elem = x
  end
  def set_elem(x)
    @elem = x
  end
  def get_next
    @next_elem
  end
  def get_prev
    @prev_elem
  end
  def get_elem
    @elem
  end
end
class Kolekcja
  def initialize(f_node)
    @first_node = f_node
    @size = 1
  end
  def add(x)
    new_first_node = Node.new(nil,x,@first_node)
    @first_node.set_prev(new_first_node)
    @first_node = new_first_node
    @size += 1
  end
  def pprint
    copy_node = @first_node
    while copy_node != nil
      puts copy_node.get_elem
      copy_node = copy_node.get_next
    end
  end
  def get_f
    @first_node
  end
  def get_size
    @size
  end
end
class Wyszukiwanie
  def get_element_at_index(kolekcja, index)
    current_node = kolekcja.get_f
    i = 0
    while current_node != nil
      return current_node.get_elem if i == index
      current_node = current_node.get_next
      i += 1
    end
    return nil
  end

  def binary_search(kolekcja, value)
    left = 0
    right = kolekcja.get_size - 1

    while left <= right
      mid = (left + right) / 2
      mid_value = get_element_at_index(kolekcja, mid)
      if mid_value > value
        left = mid + 1
      elsif mid_value < value
        right = mid - 1
      else
        return mid
      end
    end
    return nil
  end
  def interpolation_search(kolekcja, value)
    left = 0
    right = kolekcja.get_size - 1
    size = kolekcja.get_size
    while left <= right && value <= get_element_at_index(kolekcja,left) && value >= get_element_at_index(kolekcja,right)
      inter = left + (((value - get_element_at_index(kolekcja,left)) * (right - left)) / (get_element_at_index(kolekcja,right) - get_element_at_index(kolekcja,left)))
      if get_element_at_index(kolekcja,inter) == value
        return inter
      end
      if get_element_at_index(kolekcja,inter) > value
        left = inter + 1

      else
        right = inter - 1
      end
    end
    return nil
  end
end
x = Kolekcja.new(Node.new(nil ,1,nil))
x.add(2)
x.add(3)
x.pprint
w = Wyszukiwanie.new
puts w.interpolation_search(x, 1)