#ifdef GL_ES
    precision mediump float;
#endif
//Lichteigenschaften
uniform vec4 uLightPosition; 
uniform vec4 uLightAmbient; 
uniform vec4 uLightDiffuse;
uniform vec4 uLightSpecular;
//Materialeigenschaften
uniform vec4 uMaterialEmission;
uniform vec4 uMaterialAmbient;
uniform vec4 uMaterialDiffuse;
uniform vec4 uMaterialSpecular;
uniform float uMaterialShininess;
// Interpolierte Vertex und Normal Position
uniform sampler2D uSampler;

varying vec3 vVertexPos;
varying vec3 vNormalPos;
varying vec2 vTexCoord;



void main(void) {
    //Normale N, vNormalPos normalisieren da durch Interpolation kein Einheitsvektor mehr
    vec3 N = normalize(vNormalPos);
    // Eigenleuchten des Körpers
    vec4 emissiv = uMaterialEmission;
    // Ambiente Komponente "Grundreflexion"
    vec4 ambient = uMaterialAmbient * uLightAmbient;
    // Diffuse Komponente, Reflexion des Lichts in alle Richtungen
    vec4 diffuse = vec4(0,0,0,1);
    vec3 Eye = vec3(0.0, 0.0, 1.0);
    vec3 L = vec3(0.0);
    vec3 H = vec3(0.0);
    // L -> Vektor vom Punkt zur Lichtquelle
    L = normalize(vec3(uLightPosition) - uLightPosition.w * vVertexPos);
    // H -> Vektor vom Punkt zum "Auge"/Betrachter/Kamera
    H = normalize(L + Eye);
    // Spiegelnde Komponente des Lichts, spiegelung um die Perfekte Reflexion herum
    vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
    // dot(N, L) <= 0 falls Winkel über 90° ist bedeutet es trifft kein Licht auf die Oberfläche
    float a = max(dot(N, L), 0.0);
    // Berechnung falls Winkel zwischen Normaler und Licht < 90°
    if (a > 0.0) {
        //Spekular nach Blinn; Cosinus zwischen H u N durch Punktprodukt; cos^shininess für die größe der Fläche
        float specLight = pow(max(dot(H, N), 0.0), uMaterialShininess);
        //Multipliziere mit Material und Licht spekular Werten um gesamten Spekular wert für Punkt zu erhalten
        specular = vec4(vec3(specLight), 1.0) * uMaterialSpecular * uLightSpecular;
        diffuse = a*uMaterialDiffuse * uLightDiffuse;
    }
    //Kombination der Reflexion des Lichts nach Phong
    gl_FragColor = emissiv + ambient + specular + diffuse;
    gl_FragColor *= texture2D(uSampler, vec2(vTexCoord.s, vTexCoord.t));
    //gl_FragColor = vec4(vTexCoord.s, vTexCoord.t, 0, 1);
}
