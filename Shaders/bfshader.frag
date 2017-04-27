   #version 120
   
    varying vec2 texCoord;
	//uniform sampler2D lightMap;
	uniform sampler2D colorMap;

	void main(){
	//vec4 lightCol = texture2D(lightMap,texCoord.xy);
	gl_FragColor = texture2D(colorMap,texCoord.xy); 
	//+ lightCol*0.4 ;
	  
	}