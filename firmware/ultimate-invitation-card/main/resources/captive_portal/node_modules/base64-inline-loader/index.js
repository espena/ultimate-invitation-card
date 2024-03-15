const loaderUtils = require('loader-utils');
const mimeTypes = require('mime-types');

module.exports = function (content) {
    const {
        regExp,
        limit = 0,
        typeMapper = {},
        context = this.rootContext
    } = this.query;

    if (this.cacheable) {
        this.cacheable();
    }

    let extension = loaderUtils
        .interpolateName(this, '[ext]', {context, content, regExp})
        .toLowerCase();

    let mimeType = mimeTypes.lookup(extension);

    if (!mimeType) {
        throw new Error(`${extension} type is not supported.`);
    }

    if (limit > 0 && content.length > limit) {
        throw new Error(`Exceeded the recommended limit (${limit}Kb). This can impact your performance.`);
    }

    const base64 = content.toString('base64');
    const data = JSON.stringify(`data:${typeMapper[mimeType] || mimeType};charset=utf-8;base64,${base64}`);

    return `module.exports = ${data}`;
};

module.exports.raw = true;
