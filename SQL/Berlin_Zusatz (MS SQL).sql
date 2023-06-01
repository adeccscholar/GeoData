Use Geodaten;

EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Tabelle mit den Daten, die aus dem von Berliner Amt bereitgestellt wurden, übernommen wurden.',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'TABLE',  @level1name = N'Berlin';
	
EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Im Attribut "Land_ID" ist ein externe Schlüssel mit der Statistik- Kennziffer für das Land "Berlin" gespeichert. Diese Nummern werden zentral vergeben und sollten eindeutig sein.',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'TABLE',  @level1name = N'Berlin',
    @level2type = N'COLUMN', @level2name = N'Land_ID';

EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Im Attribut "Bezirk_ID" ist ein 2 stelliger, externe Schlüssel mit der Statistik- Kennziffer für Stadtbezirke im Land "Berlin" gespeichert. Sie sollte mit der Land_ID zusammen eindeutig sein. ',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'TABLE',  @level1name = N'Berlin',
    @level2type = N'COLUMN', @level2name = N'Bezirk_ID';

EXEC sys.sp_addextendedproperty 
    @name = N'MS_Description', 
    @value = N'Mit dieser Sicht werden die Bezirke aus der Tabelle extrahiert und stehen für Verknüpfungen zur Verfügung.',
    @level0type = N'SCHEMA', @level0name = N'dbo',
    @level1type = N'VIEW',  @level1name = N'vw_Berliner_Bezirke';
	