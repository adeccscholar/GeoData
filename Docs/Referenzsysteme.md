# Beschreibung der geodätischen Referenzsysteme

Diese Datei bietet eine Beschreibung der geodätischen Referenzsysteme WGS84 (World Geodetic System 1984),  ETRS89 (European Terrestrial Reference System 1989) und der Mercator-Projektion von ETRS89 sowie deren Beziehung zueinander. Geodätische Referenzsysteme sind entscheidend für die genaue Positionierung und Vermessung von Objekten auf der Erdoberfläche. Zwei der wichtigsten Referenzsysteme sind das World Geodetic System 1984 (WGS84) und das European Terrestrial Reference System 1989 (ETRS89). In diesem Artikel werden wir uns mit diesen beiden Systemen befassen, ihre Bedeutung und Verwendung in verschiedenen Anwendungen sowie ihre Besonderheiten und Unterschiede.

## WGS84 (World Geodetic System 1984)
WGS84 ist ein globales geodätisches Referenzsystem, das vom US-amerikanischen Verteidigungsministerium entwickelt und 1984 veröffentlicht wurde. Es wird weltweit in vielen Navigationssystemen wie GPS und GLONASS verwendet.

WGS84 beschreibt die Koordinaten von Punkten auf der Erdoberfläche mithilfe geodätischer Messungen und Satellitendaten. Es dient als gemeinsame Referenz für globale Vermessungen und Navigation.

Die Anwendungen von WGS84 sind vielfältig und umfassen GPS-Navigation, Luft- und Raumfahrt, Geologie, Kartographie und Geodäsie. Es ermöglicht eine präzise Bestimmung der Position und Höhe von Objekten auf der Erdoberfläche und erleichtert so die Navigation und Vermessung auf globaler Ebene.

WGS84 ist ein dynamisches System, das regelmäßig aktualisiert wird, um Veränderungen in der Erdoberfläche und der Rotation der Erde zu berücksichtigen. Neue Versionen werden veröffentlicht, um die Genauigkeit zu verbessern und das System auf dem neuesten Stand zu halten.

## ETRS89 (European Terrestrial Reference System 1989)
ETRS89 ist ein geodätisches Referenzsystem speziell für Europa. Es wurde entwickelt, um eine einheitliche Grundlage für die Vermessung und Kartierung europäischer Länder bereitzustellen. ETRS89 wurde 1989 festgelegt und ist seitdem der Standard für geodätische Vermessungen in Europa.

Ähnlich wie WGS84 beschreibt ETRS89 die Koordinaten von Punkten auf der Erdoberfläche durch geodätische Messungen und Satellitendaten. Es basiert auf einem globalen Koordinatensystem namens International Terrestrial Reference System (ITRS), das durch ein Netzwerk von Bodenstationen und Satelliten bestimmt wird.

ETRS89 wird in verschiedenen Anwendungen wie Geodäsie, Kartographie, Navigation und Luft- und Raumfahrt verwendet. Es dient als Grundlage für die Erstellung von topographischen Karten, geografischen Informationssystemen (GIS), GPS-Navigation und Bauprojektplanung.

In Europa wird ETRS89 als gemeinsames Referenzsystem für geodätische Vermessungen und den Austausch von geodätischen Daten zwischen verschiedenen Ländern verwendet. Es ermöglicht eine präzise Berechnung von Koordinaten auf der Erdoberfläche und trägt zur Vereinfachung grenzüberschreitender Vermessungen und zur Verbesserung der Genauigkeit bei.

## Mercator-Projektion von ETRS89
Die Mercator-Projektion von ETRS89 ist eine Methode, um geografische Koordinaten auf der gekrümmten Erdoberfläche des geodätischen Referenzsystems ETRS89 auf eine flache Karte zu projizieren. Sie basiert auf der klassischen Mercator-Projektion, bei der ein Zylinder um die Erde gelegt wird.

Die Mercator-Projektion hat einige Besonderheiten. Sie bewahrt Winkel und ermöglicht eine rechtwinklige Gitterstruktur auf der Karte. Dadurch eignet sich die Mercator-Projektion gut für die Navigation auf See, da Kurse als gerade Linien dargestellt werden. Jedoch führt die Projektion zu Verzerrungen in Bezug auf die Flächenverhältnisse. Gebiete in Polnähe erscheinen auf der Karte überproportional groß, während Gebiete in Äquatornähe komprimiert werden.

Um diese Verzerrungen zu minimieren, wird bei der ETRS89-Mercator-Projektion ein bestimmter Breitengrad als Referenzlinie gewählt. In Europa wird häufig der Breitengrad 52° N verwendet, der durch Deutschland, die Niederlande und andere Länder verläuft. Diese Projektion wird als "ETRS89 / UTM" (Universal Transverse Mercator) bezeichnet und teilt die Erdoberfläche in 60 Zonen auf, die jeweils 6 Grad Längenunterschied abdecken.

Jede UTM-Zone wird dann einzeln auf eine flache Karte projiziert, wodurch die Verzerrungen innerhalb der Zone minimiert werden. In Europa wird für die UTM-Zonen zusätzlich eine transversale Mercator-Projektion verwendet, bei der der Zylinder nicht parallel zum Äquator liegt, sondern entlang der Zentralmeridiane jeder Zone verläuft. Dadurch werden Verzerrungen in Nord-Süd-Richtung minimiert.

Die ETRS89-Mercator-Projektion wird in Europa häufig für kartografische Zwecke, insbesondere für topografische Karten, verwendet. Sie ermöglicht die genaue Darstellung von Geländeformen, Straßen, Gebäuden und anderen Merkmalen auf einer flachen Karte. Durch die Verwendung des ETRS89-Referenzsystems können Koordinaten präzise abgelesen und Vermessungen durchgeführt werden.

Es ist wichtig zu beachten, dass die Mercator-Projektion von ETRS89 speziell für Europa optimiert ist und außerhalb dieses Gebiets möglicherweise nicht die beste Wahl ist. In anderen Teilen der Welt werden unterschiedliche Projektionen und Referenzsysteme verwendet, die den spezifischen Anforderungen der jeweiligen Region gerecht werden.

Zusammenfassend lässt sich sagen, dass die Mercator-Projektion von ETRS89 eine gebräuchliche Methode ist, um geografische Koordinaten in Europa auf flachen Karten darzustellen. Sie ermöglicht eine genaue kartografische Darstellung, hat aber Verzerrungen in Bezug auf Flächenverhältnisse. Durch die Verwendung des ETRS89-Referenzsystems können präzise Koordinaten bestimmt und Vermessungen durchgeführt werden.

# Berechnungen im Programm

Im Vorgängerprojekt (Repository [Vergleichsprogramm](https://github.com/adeccscholar/Vergleichsprogramm)) wurden die Koordinaten und entsprechende Berechnungen in der template Struktur "Location" auf Basis von WGS84 Koordinaten realisiert. Da wesentliche Bestandteile dieses Projekt hier genutzt und erweitert werden, wird das hier forgesetzt. Deshalb werden in dieser Struktur Umwandlungen zu WGS84 bereitgestellt und die Daten in diesem gespeichert und weiterverwendet.

Diese Berechnungen basieren auf Konzepten und Beispielen, die in einem Post im Forum Stackoverflow bzw. einem Post in dem Forum der Stackexchange diskutiert wurde. Beiträge auf diesen beiden Plattformen stehen unter der Common License [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/legalcode), beide Methoden seten diese Lizenz fort.

## MyLocation::ConvertETRS89ToWGS84
Die Implementierung der Methode "ConvertETRS89ToWGS84" in der Klasse "MyLocation" basiert auf Beispielen und Posts aus Stackoverflow bzw. Stackexchange. Die Funktion verwendet den Algorithmus der Java-Methode "UTM2Deg", die unter der CC BY-SA-Lizenz steht. Gemäß den Bedingungen dieser Lizenz wird auch die C++-Implementierung unter der CC BY-SA-Lizenz veröffentlicht. Der Urheberrechtsvermerk für die C++-Methode "ConvertETRS89ToWGS84" bleibt bestehen.

Quelle: [Stackoverflow - Convert Lat/Lon to UTM](https://stackoverflow.com/questions/176137/java-convert-lat-lon-to-utm) © 2023 Stack Exchange Inc; Benutzerbeiträge lizenziert unter CC BY-SA, Benutzer: user2548538

## MyLocation::ConvertMercatorToWGS84
Die Methode "ConvertMercatorToWGS84" in der Klasse "MyLocation" basiert auf dem Algorithmus der C#-Methode "ToGeographic", die unter der CC BY-SA-Lizenz steht. 

Gemäß den Bedingungen dieser Lizenz wird auch diese Funktion unter der CC BY-SA-Lizenz freigegeben, und der Urheberrechtsvermerk für die C++-Methode "ConvertMercatorToWGS84" wird beibehalten. 

Die Quelle für den Algorithmus ist auf der Website von Stack Exchange zu finden, genauer gesagt unter folgendem Link: https://gis.stackexchange.com/questions/69208/trying-to-convert-coordinates-from-wgs84-web-mercator-auxiliary-sphere-to-wgs84. Die Rechte für den Algorithmus liegen bei Stack Exchange Inc, und die Nutzungsbedingungen sind unter der CC BY-SA-Lizenz festgelegt. Der Beitrag stammt von Benutzer BlakeG im Jahr 2023.

## Wichtige Konstanten und Begriffe bei Umrechnung "ConvertETRS89ToWGS84"

### elliptischen Abplattung (flattering)
Die Konstante 0,006739496742 ist ein Wert, der bei der Umrechnung von Geokoordinaten in kartesische Koordinaten oder umgekehrt verwendet wird. Genauer gesagt handelt es sich um den Wert der "elliptischen Abplattung" oder  "Abplattung des Erdellipsoids", die ein Maß für die Abweichung der Erde von der idealen Kugelform darstellt.

Wenn man die Erde als Kugel betrachtet, hat sie einen Radius von etwa 6.371 Kilometern. In der Realität ist die Erde jedoch an den Polen etwas abgeflacht und am Äquator etwas aufgebläht, was auf die Rotation der Erde zurückzuführen ist. Die elliptische Abplattung beschreibt dieses Phänomen und gibt an, wie stark die Erde an den Polen abgeflacht ist.

Die Konstante 0,006739496742 wird in Formeln zur Berechnung von geodätischen Entfernungen verwendet, die die elliptische Abplattung berücksichtigen. Eine solche Formel ist zum Beispiel die Haversine-Formel, die den Abstand zwischen zwei Punkten auf der Erdoberfläche berechnet. Durch Verwendung dieser Konstante in der Haversine-Formel kann man also genauere Entfernungen zwischen zwei geografischen Koordinaten berechnen, als wenn man die Erde als perfekte Kugel betrachten würde.

### Maßstabfakor (scale_factor)

Die Konstante 0,9996 wird in der Vermessungstechnik und Kartografie als Maßstabfaktor verwendet. Der Maßstabfaktor  ist ein Verhältnis zwischen der tatsächlichen Größe eines Objekts und seiner Darstellung auf einer Karte oder einem Plan.

In der Vermessungstechnik wird die Erdoberfläche aufgrund ihrer kugelförmigen Form in verschiedene geodätische Koordinatensysteme unterteilt. Das bekannteste davon ist das WGS84-System, das von GPS-Geräten verwendet wird. Um eine Karte oder einen Plan zu erstellen, muss die gekrümmte Erdoberfläche jedoch auf eine flache Ebene projiziert werden, was eine Verzerrung der Abmessungen und Formen von Flächen und Objekten zur Folge hat.

Der Maßstabfaktor 0,9996 wird speziell in der Projektion UTM (Universal Transverse Mercator) verwendet, die die Erdoberfläche in 60 Zonen unterteilt und jede dieser Zonen in eine flache Ebene projiziert. Der Maßstabfaktor von 0,9996 wird verwendet, um die Verzerrungen, die durch die Projektion der gekrümmten Erdoberfläche auf die flache Ebene entstehen, auszugleichen. Dadurch wird eine relativ genaue Abbildung der Flächen und Objekte auf der Karte erreicht.

In der Praxis bedeutet dies, dass eine Entfernung von 1.000 Metern auf der Erdoberfläche auf der UTM-Karte mit einem Maßstab von 0,9996 multipliziert wird, um die korrekte Entfernung auf der Karte zu erhalten. In diesem Fall ergibt sich eine Entfernung von 999,6 Metern.


### Mittlerer Erdradius (mean_earth_radius)
Die Zahl 6366197,724 ist ein Wert für den mittleren Erdradius. Der mittlere Erdradius ist der Radius einer fiktiven Kugel, die das Volumen und die Masse der Erde repräsentiert. Die Erde ist jedoch keine perfekte Kugel, sondern aufgrund ihrer Rotation an den Polen abgeflacht und am Äquator aufgebläht. Daher gibt es für die Erde verschiedene Radien, die je nach Anwendung verwendet werden.

Die Zahl 6366197,724 Meter wird häufig in der Geodäsie, Geophysik und Luft- und Raumfahrt verwendet, um den mittleren Erdradius zu repräsentieren. Sie wird auch in vielen Anwendungen verwendet, bei denen die Entfernungen auf der Erdoberfläche berechnet werden, wie zum Beispiel bei GPS oder geodätischen Vermessungen.

Es ist wichtig zu beachten, dass dies nur ein Näherungswert ist und dass die tatsächliche Form der Erde aufgrund ihrer Abplattung und unregelmäßigen Oberfläche komplexer ist. Wenn eine höhere Genauigkeit benötigt wird, müssen komplexere Modelle und Messungen verwendet werden, um den Radius an jedem Punkt auf der Erdoberfläche zu bestimmen.


### Polarradius (polar_earth_radius)
Die Zahl 6399593,625 ist der Polarradius der Erde, auch bekannt als der polare Erdradius. Dieser Wert gibt an, wie groß der Radius der Erde an den Polen ist, wo die Erde am stärksten abgeflacht ist. Im Gegensatz dazu ist der Äquatorradius der Erde größer aufgrund der Ausbuchtung am Äquator.

Der Polarradius der Erde ist ein wichtiger Parameter in der Geodäsie und Geophysik, da er bei der Bestimmung von Messungen, 
die auf der Erdoberfläche durchgeführt werden, berücksichtigt werden muss. Zum Beispiel kann die genaue Bestimmung der 
Erdrotation oder die Berechnung der Schwerkraft auf der Erdoberfläche nur durch Berücksichtigung des Polarradius erreicht werden.

Es ist wichtig zu beachten, dass die Erde aufgrund von Faktoren wie tektonischen Aktivitäten, Veränderungen in der 
Masseverteilung und Gezeitenkräften ein dynamisches System ist. Daher kann sich der Polarradius der Erde im Laufe der 
Zeit geringfügig ändern. Der derzeit anerkannte Wert für den Polarradius der Erde beträgt etwa 6.399.593,625 Meter.


Begriffe bei der Umrechnung der Mercator-Projektion von ETRS89 zu WGS84 "ConvertMercatorToWGS84"

Die Multiplikation von 6378137,0 mit 57,295779513082323 dient der Umrechnung der Einheit Meter auf Grad, da ETRS89 auf Meter basiert, während WGS84 auf Grad basiert.

Die Zahl 6378137,0 ist der mittlere Erdradius in Metern, der für die Mercator-Projektion von ETRS89 verwendet wird. 

Die Zahl 57,295779513082323 ist der Faktor für die Umrechnung von Radian in Grad.

In der Mercator-Projektion von ETRS89 werden Längen- und Breitengrade in Metern gemessen. Wenn Sie jedoch die Koordinaten in das geodätische Referenzsystem WGS84 umrechnen möchten, müssen Sie sie in Grad umwandeln. Dies wird durch Multiplikation der Längen- und Breitengrade mit dem Faktor 57,295779513082323 erreicht, der den Winkel in Grad anstelle von Radian angibt.

Daher bedeutet 6378137,0 * 57.295779513082323 in der Umrechnung der Mercator-Projektion von ETRS89 zu WGS84 die Umwandlung der Koordinaten von Metern in Grad, die für die WGS84-Projektion erforderlich sind.
