class Jawna
    def initialize(str)
      @napis = str
    end
    def zaszyfruj(key)
      @znapis = ""
      @napis.each_char do |i|
        @znapis += key[i]
      end
      NieJawna.new(@znapis)
    end
    def get_napis
      @napis
    end
end
class NieJawna
    def initialize(str)
        @znapis = str
    end
    def odszyfruj(key)
        @napis = ""
        @znapis.each_char do |i|
            for item in key
                if item[1] == i # value
                    @napis += item[0] # key
                end
            end
        end
        Jawna.new(@napis)
    end
    def get_znapis
        @znapis
    end
end

m = Jawna.new("ruby")
key = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
    'u' => 'a'
}

n = m.zaszyfruj(key)
puts n.get_znapis

o = n.odszyfruj(key)
puts o.get_napis
