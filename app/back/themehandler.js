const {nativeTheme} = require('electron');

/* Manage Dark mode themes with the OS's settings */
nativeTheme.on('updated', function theThemeHasChanged() {
    updateOSCOODGenTheme(nativeTheme.shouldUseDarkColors);
})
