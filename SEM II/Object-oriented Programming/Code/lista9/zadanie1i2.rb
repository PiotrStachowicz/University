# Piotr Stachowicz zadanie 1 i 2 
class Function
  def initialize(&block)
    @block = block
  end
  def value(x)
    @block.call(x)
  end
  def zero(a, b, e)
    if (a-b).abs<e
      return nil
    end
    c = (a + b) / 2
    w = value(c)
    if w.abs < e
      return c
    end
    if value(a) * value(c) < 0
      zero(a, c, e)
    else
      zero(c, b, e)
    end
  end
  def field(a,b)
    n = 1000.0
    dx = (b-a)/n
    pole = 0.0
    for i in 0...n
      xi = (i+0.5)*dx
      pole = pole + (value(xi)*dx)
    end
    pole
  end
  def deriv(x)
    h = 0.00000000001
    y1 = value(x+h)
    y2 = value(x)
    (y1-y2)/h
  end
  def max(a,b)
    if deriv(1)>0
      value(b)
    else
      value(a)
    end
  end
  def plot(a, b)
    dy = 0.5
    maxy = ((max(a, b).round(1).abs) * 10).to_i + 1
    maxx = ((b - a) * 10).to_i + 1
    for y in 0...maxy
      rY = (maxy/2 - y)
      for x in 0...maxx
        rX = (x - maxx/2).to_f
        if y == maxy / 2
          print "-"
        elsif x == maxx / 2
          print "|"
        elsif (value(rX) - rY).abs < dy
          print "*"
        else
          print " "
        end
      end
      puts
    end
  end
end
# x
fun1 = Function.new { | x | x}
puts fun1.field(0,2)
puts fun1.deriv(2)
fun1.plot(0,4)
puts
# x^2
fun2 = Function.new { | x | x*x}
puts fun2.field(0,2)
puts fun2.deriv(2)
fun2.plot(0,4)
puts
# sin(x)
fun3 = Function.new { | x | Math.sin(x)}
puts fun3.field(0,2)
puts fun3.deriv(2)
fun3.plot(0,4)
puts