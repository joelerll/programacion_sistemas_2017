var gulp = require('gulp');
var shell = require('shelljs');
gulp.task('default', function() {
  gulp.watch('*.c', ['mensaje']);
});

gulp.task('mensaje', function() {
    shell.exec('make');
    shell.echo('cambiado');
})
