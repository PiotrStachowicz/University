#Piotr Stachowicz
class Mass
  def initialize(kg)
    @kilograms = kg
    @funts = kg_to_fun
  end
  def kg_to_fun
    @funts = @kilograms * 2.20462
  end
  def fun_to_kg
    @kilograms = @funts / 2.20462
  end
  def get_values
    [@kilograms, "kilo", @funts, "funts"]
  end
end

class Length
  def initialize(len)
    @meters = len
    @yard = meters_to_yard
  end
  def meters_to_yard
    @yard = @meters * 0.9144
  end
  def yard_to_meters
    @meters = @yard / 0.9144
  end
  def get_values
    [@meters, "meters", @yard, "yards"]
  end
end

class Surface
  def initialize(len, len2)
    @len1 = Length.new(len)
    @len2 = Length.new(len2)
    @hectares = (@len1.get_values)[0]*(@len2.get_values)[0] / 10000.0
    @sqr_inches = hec_to_square_inches
  end
  def hec_to_square_inches
    @sqr_inches = @hectares * 15500031.0
  end
  def square_inches_to_hectares
    @hectares = @sqr_inches / 15500031.0
  end
  def get_values
    [@hectares, "hectares", @sqr_inches, "square inches"]
  end
end

class Pressure
  def initialize(len1, len2, kg)
    @sur = Surface.new(len1, len2)
    @mass = Mass.new(kg)
    @psi = ((@mass.get_values)[2]  * 9.806) / (@sur.get_values)[2] # pounds per square inch
    @bars = psi_to_bars
  end
  def bars_to_psi
    @psi = @bars * 14.5038
  end
  def psi_to_bars
    @bars = @psi / 14.5038
  end
  def get_values
    [@bars, "bars", @psi, "psi"]
  end
end

mass = Mass.new(15) # 15kg
len = Length.new(42) # 42 metry
sur = Surface.new(40, 400) # 1.6 hektara
pre = Pressure.new(1,1,1200000) # 16 000 PSI, tyle co w Rowie Mariańskim
tab = [mass, len, sur, pre]
def put_table(tab1)
  tab1.each do |obj|
    x = obj.get_values
    puts "#{x[0]} #{x[1]} -> #{x[2]} #{x[3]}"
  end
end
put_table(tab)

