module.exports = (config) => {
  config.set({
    // base path that will be used to resolve all patterns (eg. files, exclude)
    basePath: "./",
    captureTimeout: 120000,
    reportSlowerThan: 500,
    browserNoActivityTimeout: 240000,

    // frameworks to use
    // available frameworks: https://npmjs.org/browse/keyword/karma-adapter
    frameworks: ["jasmine", "karma-typescript"],

    // list of files / patterns to load in the browser
    files: ["test/**/*.ts", "src/**/*.ts"],

    // list of files / patterns to exclude
    exclude: ["**/*.d.ts", "dist/**/*"],

    preprocessors: {
      "test/**/*.ts": ["karma-typescript"],
      "src/**/*.ts": ["karma-typescript", "coverage"],
    },

    karmaTypescriptConfig: {
      compilerOptions: {
        noImplicitUseStrict: true,
        esModuleInterop: true,
      },
      exclude: ["node_modules", "dist", ".vscode"],
      bundlerOptions: {
        transforms: [
          require("karma-typescript-es6-transform")({
            presets: ["@babel/preset-env"],
          }),
        ],
      },
    },
    // 新增 coverageReporter选项
    // 配置覆盖率报告的查看方式,type查看类型，可取值html、text等等，dir输出目录
    coverageReporter: {
      type: "text",
      dir: "coverage/",
    },

    // 添加配置报告选择
    reporters: ["progress", "coverage"],

    // web server port
    port: 9876,

    // enable / disable colors in the output (reporters and logs)
    colors: true,

    // level of logging
    // possible values: config.LOG_DISABLE || config.LOG_ERROR || config.LOG_WARN || config.LOG_INFO || config.LOG_DEBUG
    logLevel: config.LOG_INFO,

    // enable / disable watching file and executing tests whenever any file changes
    autoWatch: true,

    // start these browsers
    // available browser launchers: https://npmjs.org/browse/keyword/karma-launcher
    browsers: ["ChromeHeadless"],

    customLaunchers: {},

    // Continuous Integration mode
    // if true, Karma captures browsers, runs the tests and exits
    singleRun: false,

    // Concurrency level
    // how many browser should be started simultaneous
    concurrency: Infinity,

    plugins: [
      "karma-coverage",
      "karma-jasmine",
      "karma-chrome-launcher",
      "karma-typescript",
    ],
  });
};
